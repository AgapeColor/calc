#pragma once

#include <boost/asio.hpp>

#include <atomic>
#include <cstdint>

class RequestHandler;

class TcpServer {
public:
    TcpServer(std::uint16_t port, RequestHandler& requestHandler);

    void run();
    void stop();

private:
    std::uint16_t port_;
    RequestHandler& requestHandler_;
    std::atomic_bool stopRequested_;
    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
};
