#include "logger.h"

#include <postgres_result.h>

PostgresResult::PostgresResult(PGresult* result) : result_(result) {
    if (result_ != nullptr) {
        Logger::instance().debug("Database query result acquired");
    }
}

PostgresResult::PostgresResult(PostgresResult&& obj) noexcept : result_(obj.result_) {
    obj.result_ = nullptr;

    if (result_ != nullptr) {
        Logger::instance().debug("Database query result moved");
    }
}

PostgresResult& PostgresResult::operator=(PostgresResult&& obj) noexcept {
    if (this == &obj) {
        return *this;
    }
    if (result_ != nullptr) {
        PQclear(result_);
    }
    result_ = obj.result_;
    obj.result_ = nullptr;

    if (result_ != nullptr) {
        Logger::instance().debug("Database query result move-assigned");
    }
    return *this;
}

PostgresResult::~PostgresResult() {
    if (result_ != nullptr) {
        PQclear(result_);
        Logger::instance().debug("Database query result cleared");
    }
}
