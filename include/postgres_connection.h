#pragma once

#include <postgresql/libpq-fe.h>
#include <string>

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

private:
    PGconn* conn_ = nullptr;
};