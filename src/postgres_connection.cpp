#include "postgres_connection.h"
#include "logger.h"
#include "postgres_result.h"
#include "operation_record.h"
#include "sql_queries.h"

#include <stdexcept>
#include <string>

PostgresConnection::PostgresConnection(const std::string& connectionString) {
    Logger::instance().debug("Connecting to database");

    conn_.reset(PQconnectdb(connectionString.c_str()));

    if (!conn_) {
        Logger::instance().error("Failed to create database connection object");
        throw std::runtime_error("Failed to create database connection object");
    }

    if (PQstatus(conn_.get()) != CONNECTION_OK) {
        std::string error = PQerrorMessage(conn_.get());
        Logger::instance().error("Database connection failed: " + error);
        throw std::runtime_error(error);
    }

    Logger::instance().debug("Database connection established");
}

PostgresConnection::~PostgresConnection() {
    if (conn_) {
        Logger::instance().debug("Database connection closed");
    }
}

PostgresResult PostgresConnection::executeQuery(const std::string& query) {
    Logger::instance().debug("Executing query");

    PostgresResult result(PQexec(conn_.get(), query.c_str()));

    if (result.get() == nullptr) {
        std::string error = PQerrorMessage(conn_.get());
        Logger::instance().error("Query execution failed: " + error);
        throw std::runtime_error("Query execution failed: " + error);
    }

    if (result.status() != PGRES_TUPLES_OK && result.status() != PGRES_COMMAND_OK) {
        std::string error = result.errorMsg();
        Logger::instance().error("Query execution failed: " + error);
        throw std::runtime_error("Query execution failed: " + error);
    }

    Logger::instance().debug("Query executed successfully");

    return result;
}

PostgresResult PostgresConnection::executeParamQuery(const std::string& query, const std::vector<const char*>& params) {
    Logger::instance().debug("Executing parameterized query");

    PostgresResult result(
        PQexecParams(
            conn_.get(),
            query.c_str(),
            static_cast<int>(params.size()),
            nullptr,
            params.data(),
            nullptr,
            nullptr,
            0
        )
    );

    if (result.get() == nullptr) {
        std::string error = PQerrorMessage(conn_.get());
        Logger::instance().error("Parameterized query execution failed: " + error);
        throw std::runtime_error("Parameterized query execution failed: " + error);
    }

    if (result.status() != PGRES_TUPLES_OK && result.status() != PGRES_COMMAND_OK) {
        std::string error = result.errorMsg();
        Logger::instance().error("Parameterized query execution failed: " + error);
        throw std::runtime_error("Parameterized query execution failed: " + error);
    }

    Logger::instance().debug("Parameterized query executed successfully");

    return result;
}

void PostgresConnection::saveOperation(const OperationRecord& record) {
    std::string arg1Str = std::to_string(record.arg1_);
    std::string arg2Str = std::to_string(record.arg2_);
    std::string resultStr;
    if (record.result_.has_value()) {
        resultStr = std::to_string(*record.result_);
    }
    std::string statusStr = std::to_string(record.status_);

    std::vector<const char*> params = {
        record.operation_.c_str(),
        arg1Str.c_str(),
        arg2Str.c_str(),
        record.result_.has_value() ? resultStr.c_str() : nullptr,
        statusStr.c_str()
    };

    executeParamQuery(SqlQueries::InsertOperation, params);
}
