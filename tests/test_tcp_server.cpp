#include <gtest/gtest.h>
#include "request_handler.h"
#include "postgres_connection.h"
#include "cache.h"
#include "tcp_server.h"

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include <chrono>
#include <cstdint>
#include <istream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

TEST(TcpServerTest, returnsCalculationResult) {
    namespace asio = boost::asio;
    using tcp = asio::ip::tcp;

    PostgresConnection dataBase("host=localhost dbname=calc_db user=calc_user password=calc");
    Cache cache;
    RequestHandler handler(dataBase, cache);

    constexpr std::uint16_t testPort = 28080;

    TcpServer server(testPort, handler);

    std::thread serverThread([&server]() {
        server.run();
    });

    asio::io_context ioContext;
    tcp::endpoint endpoint(
        asio::ip::make_address("127.0.0.1"),
        testPort
    );

    std::unique_ptr<tcp::socket> socket;

    bool connected = false;
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(1);

    while (!connected && std::chrono::steady_clock::now() < deadline) {
        auto attemptSocket = std::make_unique<tcp::socket>(ioContext);

        boost::system::error_code error;
        auto connectResult = attemptSocket->connect(endpoint, error);

        if (!connectResult) {
            connected = true;
            socket = std::move(attemptSocket);
        }
    }
    if (!connected) {
        server.requestStop();
        serverThread.join();
        FAIL() << "Failed to connect to test TCP server";
    }

    ASSERT_NE(socket, nullptr);
    tcp::socket& connectedSocket = *socket;

    std::string response;

    try {
        std::string request = R"({"op":"add","a":2,"b":3})";
        request += '\n';

        asio::write(connectedSocket, asio::buffer(request));

        asio::streambuf buffer;
        asio::read_until(connectedSocket, buffer, '\n');

        std::istream input(&buffer);
        std::getline(input, response);

        auto data = nlohmann::json::parse(response);
        EXPECT_EQ(data.at("result").get<int>(), 5);
    }
    catch (...) {
        server.requestStop();
        serverThread.join();
        throw;
    }

    server.requestStop();
    serverThread.join();
}

