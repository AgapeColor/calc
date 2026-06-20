#include "runner.h"
#include "logger.h"
#include "postgres_connection.h"
#include "postgres_result.h"
#include "sql.h"
#include "cache.h"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    Logger::instance().info("Application is started");
    try {
        PostgresConnection dataBase("host=localhost dbname=calc_db user=calc_user password=calc");
        dataBase.executeQuery(SqlQueries::CreateOperationsTable);
        
        Cache cache;
        cache.load(dataBase.loadHistory());

        Runner appRunner(dataBase, cache);
        appRunner.run(argc, argv);
        
        Logger::instance().info("Application is finished");
        return 0;
    }
    catch (const std::exception& e) {
        Logger::instance().error(std::string("Fatal error: ") + e.what());
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

