#include "runner.h"
#include "postgres_connection.h"
#include "cache.h"
#include "request_handler.h"
#include "printer.h"

#include <stdexcept>

Runner::Runner(PostgresConnection& dataBase, Cache& cache) 
    : dataBase_(dataBase),
      cache_(cache)
{}

void Runner::run(int argc, char** argv) {
    if (argc < 2) {
        throw std::invalid_argument("JSON argument is missed");
    }

    std::string rawRequest = argv[1];

    RequestHandler handler(dataBase_, cache_);

    Context result = handler.handle(rawRequest);

    Printer::print_result(result);
}
