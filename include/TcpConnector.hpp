#pragma once

#include "EpollHandler.hpp"

class TcpConnector : public EpollHandler
{
public:
    using NewConnectionCallback = std::function<void(TcpChannelPtr)>;

    TcpConnector(EventPollerPtr& poller);
    void HandleErrorEvent(TcpChannelPtr tcpChan) override;
    void HandleReadEvent(TcpChannelPtr tcpChan) override;
    void HandleWriteEvent(TcpChannelPtr tcpChan) override;
    void SetNewConnectionCallback(NewConnectionCallback callback);
    void Connect(const std::string& domainName, uint16_t port);
    ~TcpConnector() override = default;

private:
    NewConnectionCallback callback_;
};
