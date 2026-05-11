#include "runner.h"
#include "logger.h"
#include "postgres_connection.h"
#include "postgres_result.h"
#include "sql.h"
#include "operation_record.h"

#include <vector>
#include <stdexcept>

void Runner::run(int argc, char** argv) {
    Logger::instance().info("Application is started");

    PostgresConnection dataBase("host=localhost dbname=calc_db user=calc_user password=calc");
    dataBase.executeQuery(SqlQueries::CreateOperationsTable);
    
    std::vector<OperationRecord> history = dataBase.loadHistory();
    cache_.load(history);

    parser_.parse_args(argc, argv, ctx_);
    Checker::check_args(ctx_);

    OperationRecord dbRecord = OperationRecord::fromContext(ctx_);

    if (cache_.contains(dbRecord)) {
        ctx_ = cache_.get(dbRecord).toContext();
    }
    else {
        std::exception_ptr savedException;
        try {
            Calculator::calculate(ctx_);
        } catch (const std::runtime_error&) {
            savedException = std::current_exception();
        }
        dbRecord = OperationRecord::fromContext(ctx_);
        cache_.insert(dbRecord);
        try {
            dataBase.saveOperation(dbRecord);
        } catch (std::runtime_error&) {
            Logger::instance().error("Failed to save operation to database");
        }
        if (savedException) {
            std::rethrow_exception(savedException);
        }
    }

    Printer::print_result(ctx_);

    Logger::instance().info("Application is finished");
}
