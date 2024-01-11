#pragma once

#include "HttpClient.hpp"
#include "SinaStockParser.hpp"

class SinaStockClient
{
public:
    SinaStockClient(EpollerPtr& epoller);
    void Connect();
    bool IsConnect() const;
    void GetStock(const std::string& stockId);
    ~SinaStockClient() = default;

private:
    void StockDecodeCallback(const std::string& msg);
    HttpRequest ConstructStockRequest(const std::string& stockId);
    void WaitUntilConnect() const;

private:
    const std::string sinaStockDomainName = "hq.sinajs.cn";
    const uint16_t sinaStockDomainPort = 80;
    HttpClient httpClient_;
    SinaStockParser stockParser_;
};
