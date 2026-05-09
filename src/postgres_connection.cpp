#include "postgres_connection.h"
#include "logger.h"
#include "postgres_result.h"

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
