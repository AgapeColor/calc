#include "runner.h"
#include "logger.h"
#include "postgres_connection.h"
#include "postgres_result.h"
#include "sql_queries.h"

void Runner::run(int argc, char** argv) {
    Logger::instance().info("Application is started");

    PostgresConnection dataBase("host=localhost dbname=calc_db user=calc_user password=calc");
    dataBase.executeQuery(SqlQueries::CreateOperationsTable);

    parser_.parse_args(argc, argv, ctx_);
    Checker::check_args(ctx_);
    Calculator::calculate(ctx_);
    Printer::print_result(ctx_);

    Logger::instance().info("Application is finished");
}
