#include "printer.h"
#include "application.h"
#include "logger.h"
#include "postgres_connection.h"
#include "postgres_result.h"
#include "sql.h"
#include "cache.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "-h" || arg1 == "--help") {
            Printer::print_help(argv[0]);
            return 0;
        }
    }

    Logger::instance().info("Application is started");
    try {
        PostgresConnection dataBase("host=localhost dbname=calc_db user=calc_user password=calc");
        dataBase.executeQuery(SqlQueries::CreateOperationsTable);
        
        Cache cache;
        cache.load(dataBase.loadHistory());

        Application application(dataBase, cache);
        application.run();
        
        Logger::instance().info("Application is finished");
        return 0;
    }
    catch (const std::exception& e) {
        Logger::instance().error(std::string("Fatal error: ") + e.what());
        Logger::instance().info("Application is finished with error");
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

