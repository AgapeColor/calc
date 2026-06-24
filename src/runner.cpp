#include "runner.h"
#include "postgres_connection.h"
#include "cache.h"
#include "request_handler.h"
#include "tcp_server.h"

#include <stdexcept>
#include <cstdint>

Runner::Runner(PostgresConnection& dataBase, Cache& cache) 
    : dataBase_(dataBase),
      cache_(cache)
{}

void Runner::run(int argc, char** argv) {
    (void)argc;
    (void)argv;

    constexpr std::uint16_t serverPort = 8080;

    RequestHandler handler(dataBase_, cache_);

    TcpServer server(serverPort, handler);

    server.run();
}
