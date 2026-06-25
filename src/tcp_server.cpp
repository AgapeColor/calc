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

TcpServer::TcpServer(std::uint16_t port, RequestHandler& requestHandler)
    : port_(port),
      requestHandler_(requestHandler),
      stopRequested_(false),
      acceptor_(ioContext_)
{}

void TcpServer::run() {
    stopRequested_.store(false);
    ioContext_.restart();

    namespace asio = boost::asio;
    using tcp = asio::ip::tcp;

    tcp::endpoint endpoint(tcp::v4(), port_);

    if (acceptor_.is_open()) {
        boost::system::error_code error;
        acceptor_.close(error);
    }

    acceptor_.open(endpoint.protocol());
    acceptor_.bind(endpoint);
    acceptor_.listen();

    std::cout << "Server started on port " << port_ << std::endl;

    while (!stopRequested_.load()) {
        tcp::socket socket(ioContext_);

        boost::system::error_code error;
        acceptor_.accept(socket, error);

        if (error) {
            if (stopRequested_.load()) {
                break;
            }
            Logger::instance().error("Accept error: " + error.message());
            continue;
        }

        Logger::instance().info("Client connected: " + socket.remote_endpoint().address().to_string());

        try {
            asio::streambuf buffer;
            asio::read_until(socket, buffer, '\n');

            std::istream input(&buffer);

            std::string request;
            std::getline(input, request);
            Logger::instance().debug("Received request: " + request);

            Context ctx = requestHandler_.handle(request);

            std::string response = ResponseSerializer::resultToJson(ctx);
            response += '\n';
            asio::write(socket, asio::buffer(response));
        }
        catch (const RequestError& e) {
            Logger::instance().error(std::string("Request error: ") + e.what());
            std::string response = ResponseSerializer::errorToJson("request", e.what());
            response += '\n';
            asio::write(socket, asio::buffer(response));
        }
        catch (const MathError& e) {
            Logger::instance().error(std::string("Math error: ") + e.what());
            std::string response = ResponseSerializer::errorToJson("math", e.what());
            response += '\n';
            asio::write(socket, asio::buffer(response));
        }
        catch (const std::exception& e) {
            Logger::instance().error(std::string("Internal error: ") + e.what());
            std::string response = ResponseSerializer::errorToJson("internal", "INTERNAL_ERROR");
            response += '\n';
            asio::write(socket, asio::buffer(response));
        }
    }
}

void TcpServer::stop() {
    stopRequested_.store(true);
    boost::system::error_code error;
    acceptor_.close(error);
    ioContext_.stop();
}
