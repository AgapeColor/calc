#pragma once

#include <postgresql/libpq-fe.h>
#include <memory>
#include <string>

class PostgresResult {
public:
    explicit PostgresResult(PGresult* result) : result_(result) {}

    PostgresResult(const PostgresResult& obj) = delete;
    PostgresResult& operator=(const PostgresResult& obj)  = delete;
    PostgresResult(PostgresResult&& obj) noexcept = default;
    PostgresResult& operator=(PostgresResult&& obj) noexcept = default;

    ~PostgresResult() = default;

    ExecStatusType status() const { return PQresultStatus(result_.get()); }
    std::string errorMsg() const { return PQresultErrorMessage(result_.get()); }
    PGresult* get() const { return result_.get(); }

    int rowsCount() const { return PQntuples(result_.get()); }
    int columnsCount() const { return PQnfields(result_.get()); }
    bool isNull(int row, int col) const { return PQgetisnull(result_.get(), row, col); }
    std::string cellValue(int row, int col) const { return std::string(PQgetvalue(result_.get(), row, col)); }

private:
    struct resDeleter {
        void operator()(PGresult* result) const noexcept {
            if (result) {
                PQclear(result);
            }
        }
    };
    std::unique_ptr<PGresult, resDeleter> result_;
};
