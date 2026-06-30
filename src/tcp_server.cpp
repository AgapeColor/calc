#include "tcp_server.h"

#include "request_handler.h"
#include "response_serializer.h"
#include "logger.h"
#include "app_error.h"

#include <boost/asio.hpp>

#include <string>
#include <istream>
#include <iostream>
#include <exception>
#include <memory>

TcpServer::TcpServer(std::uint16_t port, RequestHandler& requestHandler)
    : port_(port),
      requestHandler_(requestHandler),
      stopRequested_(false),
      acceptor_(ioContext_)
{}

void TcpServer::run() {
    stopRequested_.store(false);
    ioContext_.restart();

    using tcp = boost::asio::ip::tcp;

    tcp::endpoint endpoint(tcp::v4(), port_);

    if (acceptor_.is_open()) {
        boost::system::error_code error;
        auto closeResult = acceptor_.close(error);

        if (closeResult) {
            Logger::instance().error("Failed to close acceptor: " + closeResult.message());
        }
    }

    acceptor_.open(endpoint.protocol());
    acceptor_.bind(endpoint);
    acceptor_.listen();

    std::cout << "Server started on port " << port_ << std::endl;

    startAccept();

    ioContext_.run();
}

void TcpServer::requestStop() {
    stopRequested_.store(true);
    boost::asio::post(
        ioContext_,
        [this]() {
            boost::system::error_code error;
            auto closeResult = acceptor_.close(error);

            if (closeResult) {
                Logger::instance().error("Failed to close acceptor: " + closeResult.message());
            }

            ioContext_.stop();
    });
}

void TcpServer::startAccept() {
    using tcp = boost::asio::ip::tcp;

    auto socket = std::make_shared<tcp::socket>(ioContext_);

    acceptor_.async_accept(
        *socket,
        [this, socket](const boost::system::error_code& error) {
            if (error) {
                if (!stopRequested_.load()) {
                    Logger::instance().error("Accept error: " + error.message());
                    startAccept();
                }
                return;
            }

            Logger::instance().info(
                "Client connected: " +
                socket->remote_endpoint().address().to_string()
            );

            handleClient(socket);
        }
    );
}

void TcpServer::handleClient(const std::shared_ptr<boost::asio::ip::tcp::socket>& socket) {
    namespace asio = boost::asio;

    try {
        asio::streambuf buffer;
        asio::read_until(*socket, buffer, '\n');

        std::istream input(&buffer);

        std::string request;
        std::getline(input, request);
        Logger::instance().debug("Received request: " + request);

        Context ctx = requestHandler_.handle(request);

        std::string response = ResponseSerializer::resultToJson(ctx);
        response += '\n';
        asio::write(*socket, asio::buffer(response));
    }
    catch (const RequestError& e) {
        Logger::instance().error(std::string("Request error: ") + e.what());
        std::string response = ResponseSerializer::errorToJson("request", e.what());
        response += '\n';
        asio::write(*socket, asio::buffer(response));
    }
    catch (const MathError& e) {
        Logger::instance().error(std::string("Math error: ") + e.what());
        std::string response = ResponseSerializer::errorToJson("math", e.what());
        response += '\n';
        asio::write(*socket, asio::buffer(response));
    }
    catch (const std::exception& e) {
        Logger::instance().error(std::string("Internal error: ") + e.what());
        std::string response = ResponseSerializer::errorToJson("internal", "INTERNAL_ERROR");
        response += '\n';
        asio::write(*socket, asio::buffer(response));
    }
    if (!stopRequested_.load()) {
        startAccept();
    }
}
