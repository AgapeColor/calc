#include "logger.h"
#include "postgres_result.h"

#include <postgres_connection.h>
#include <stdexcept>
#include <string>

PostgresConnection::PostgresConnection(const std::string& connectionString) {
    Logger::instance().debug("Connecting to database");
    conn_ = PQconnectdb(connectionString.c_str());

    if (conn_ == nullptr) {
        Logger::instance().error("Failed to create database connection object");
        throw std::runtime_error("Failed to create database connection object");
    }

    if (PQstatus(conn_) != CONNECTION_OK) {
        std::string error = PQerrorMessage(conn_);
        PQfinish(conn_);
        conn_ = nullptr;
        Logger::instance().error("Database connection failed: " + error);
        throw std::runtime_error(error);
    }

    Logger::instance().debug("Database connection established");
}

PostgresConnection::~PostgresConnection() {
    if (conn_ != nullptr) {
        PQfinish(conn_);
        Logger::instance().debug("Database connection closed");
    }
}

PostgresResult PostgresConnection::executeQuery(const std::string& query) {
    Logger::instance().debug("Executing query");

    PGresult* rawRes = PQexec(conn_, query.c_str());

    if (rawRes == nullptr) {
        Logger::instance().error("Query execution failed: null result");
        throw std::runtime_error("Query execution failed: null result");
    }

    ExecStatusType rawResStatus = PQresultStatus(rawRes);

    if (rawResStatus != PGRES_TUPLES_OK && rawResStatus != PGRES_COMMAND_OK) {
        std::string error = PQresultErrorMessage(rawRes);
        PQclear(rawRes);
        Logger::instance().error("Query execution failed: " + error);
        throw std::runtime_error("Query execution failed: " + error);
    }

    Logger::instance().debug("Query executed successfully");

    return PostgresResult(rawRes);
}
