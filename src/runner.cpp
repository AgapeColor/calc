#include "runner.h"
#include "logger.h"
#include "operation_record.h"
#include <stdexcept>

Runner::Runner(PostgresConnection& dataBase, Cache& cache) 
    : dataBase_(dataBase),
      cache_(cache)
{}

void Runner::run(int argc, char** argv) {
    parser_.parse_args(argc, argv, ctx_);
    Checker::check_args(ctx_);

    OperationRecord dbRecord = OperationRecord::fromContext(ctx_);

    if (cache_.contains(dbRecord)) {
        Logger::instance().debug("Cache hit");
        ctx_ = cache_.get(dbRecord).toContext();
    }
    else {
        Logger::instance().debug("Cache miss, calculating...");
        std::exception_ptr savedException;
        try {
            Calculator::calculate(ctx_);
        } catch (const std::runtime_error&) {
            savedException = std::current_exception();
        }
        dbRecord = OperationRecord::fromContext(ctx_);
        cache_.insert(dbRecord);
        try {
            dataBase_.saveOperation(dbRecord);
        } catch (std::runtime_error&) {
            Logger::instance().error("Failed to save operation to database");
        }
        if (savedException) {
            std::rethrow_exception(savedException);
        }
    }

    Printer::print_result(ctx_);
}
