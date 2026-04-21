#include "logger.h"

#include <postgres_connection.h>
#include <stdexcept>
#include <string>

PostgresConnection::PostgresConnection(const std::string& connectionString) {
    Logger::instance().debug("Connecting to database...");
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

    Logger::instance().debug("Connected to database");
}

PostgresConnection::~PostgresConnection() {
    if (conn_ != nullptr) {
        PQfinish(conn_);
        Logger::instance().debug("Database connection closed");
    }
    conn_ = nullptr;
}
