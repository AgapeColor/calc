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
