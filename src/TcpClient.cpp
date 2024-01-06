#include <stdexcept>

#include <sys/epoll.h>
#include <unistd.h>

#include "Logger.hpp"
#include "TcpClient.hpp"

TcpClient::TcpClient()
    : epollFd_(epoll_create(EPOLL_MAX_EVENT))
    , events_(32)
    , isQuit_(false)
{}

void TcpClient::AddEvent(std::shared_ptr<TcpConnection>& conn, uint32_t event)
{
    EpollEventCtl(conn.get(), EPOLL_CTL_ADD, event);
}

void TcpClient::ModEvent(std::shared_ptr<TcpConnection>& conn, uint32_t event)
{
    EpollEventCtl(conn.get(), EPOLL_CTL_MOD, event);
}

void TcpClient::DelEvent(std::shared_ptr<TcpConnection>& conn)
{
    EpollEventCtl(conn.get(), EPOLL_CTL_DEL, 0);
}

void TcpClient::Run()
{
    epollThread_ =
        std::make_shared<std::thread>(&TcpClient::EpollThreadFn, this);
}

void TcpClient::EpollThreadFn()
{
    while (!isQuit_) {
        auto conns = PollEvent();
        HandleEvent(conns);
    }
}

std::vector<TcpConnection*> TcpClient::PollEvent()
{
    std::vector<TcpConnection*> conns;
    int eventCnt =
        ::epoll_wait(epollFd_, events_.data(), EPOLL_MAX_EVENT, EPOLL_TIMEOUT);
    DEBUG("eventCnt {}\n", eventCnt);
    if (eventCnt == -1) {
        throw std::runtime_error(
            fmt::format("Fail to epoll_wait {} {}\n", eventCnt, errno));
    } else if (eventCnt == 0) {
        // Timeout rings
        return conns;
    }
    for (int i = 0; i < eventCnt; i++) {
        auto conn = static_cast<TcpConnection*>(events_[i].data.ptr);
        conn->SetEvent(events_[i].events);
        conns.emplace_back(conn);
    }
    return conns;
}

void TcpClient::HandleEvent(std::vector<TcpConnection*>& conns)
{
    for (auto& conn : conns) {
        uint32_t event = conn->GetEvent();
        DEBUG("Epoll event {:x}\n", event);
        if (event & EPOLLERR) {
            conn->OnErrorable();
        }
        if (event & EPOLLOUT) {
            conn->OnWritable();
        }
        if (event & EPOLLIN) {
            conn->OnReadable();
        }
    }
}

void TcpClient::EpollEventCtl(TcpConnection* conn, int op, uint32_t event)
{
    struct epoll_event epollEvt;
    epollEvt.data.ptr = static_cast<void*>(conn);
    epollEvt.events = event;

    int ret = ::epoll_ctl(epollFd_, op, conn->GetSock()->GetFd(), &epollEvt);
    if (ret == -1) {
        throw std::runtime_error(
            fmt::format("Fail to {} epoll event {}\n", op, event));
    }
}

TcpClient::~TcpClient()
{
    isQuit_ = true;
    if (epollThread_->joinable()) {
        epollThread_->join();
    }
    ::close(epollFd_);
}
