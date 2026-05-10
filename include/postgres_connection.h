#pragma once

#include <postgresql/libpq-fe.h>
#include <memory>
#include <string>
#include <vector>

class PostgresResult;

class PostgresConnection {
public:
    PostgresConnection(const std::string& connectionString);

    PostgresConnection(const PostgresConnection& obj) = delete;
    PostgresConnection& operator=(const PostgresConnection& obj) = delete;
    PostgresConnection(PostgresConnection&& obj) = delete;
    PostgresConnection& operator=(PostgresConnection&& obj) = delete;

    ~PostgresConnection();

    PostgresResult executeQuery(const std::string& query);
    PostgresResult executeParamQuery(const std::string& query, const std::vector<const char*>& params);

private:
    struct connDeleter {
        void operator()(PGconn* conn) const noexcept {
            if (conn) {
                PQfinish(conn);
            }
        }
    };
    std::unique_ptr<PGconn, connDeleter> conn_;
};
