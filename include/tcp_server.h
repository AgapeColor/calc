#pragma once

#include <cstdint>
#include <string>

class RequestHandler;

class TcpServer {
public:
    TcpServer(std::uint16_t port, RequestHandler& requestHandler);

    void run();

private:
    std::uint16_t port_;
    RequestHandler& requestHandler_;
};
