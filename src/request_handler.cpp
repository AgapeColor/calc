#include "request_handler.h"
#include "postgres_connection.h"
#include "cache.h"
#include "context.h"
#include "parser.h"
#include "checker.h"
#include "operation_record.h"
#include "logger.h"
#include "calculator.h"

#include <exception>
#include <stdexcept>

RequestHandler::RequestHandler(PostgresConnection& dataBase, Cache& cache)
    : dataBase_(dataBase),
      cache_(cache)
{}

Context RequestHandler::handle(const std::string& rawRequest) {
    Context ctx;

    parser_.parse_json(rawRequest, ctx);
    Checker::check_args(ctx);

    OperationRecord dbRecord = OperationRecord::fromContext(ctx);

    if (cache_.contains(dbRecord)) {
        Logger::instance().debug("Cache hit");
        ctx = cache_.get(dbRecord).toContext();
    }
    else {
        Logger::instance().debug("Cache miss, calculating...");
        std::exception_ptr savedException;

        try {
            Calculator::calculate(ctx);
        }
        catch (const std::runtime_error&) {
            savedException = std::current_exception();
        }

        dbRecord = OperationRecord::fromContext(ctx);
        cache_.insert(dbRecord);
        
        try {
            dataBase_.saveOperation(dbRecord);
        } 
        catch (std::runtime_error&) {
            Logger::instance().error("Failed to save operation to database");
        }

        if (savedException) {
            std::rethrow_exception(savedException);
        }
    }
    return ctx;
}
