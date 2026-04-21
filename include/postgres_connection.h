#pragma once

#include <postgresql/libpq-fe.h>
#include <string>

class PostgresConnection {
public:
    PostgresConnection(const std::string& connectionString);

    PostgresConnection(const PostgresConnection& obj) = delete;
    PostgresConnection& operator=(const PostgresConnection& obj) = delete;
    PostgresConnection(PostgresConnection&& obj) = delete;
    PostgresConnection& operator=(PostgresConnection&& obj) = delete;

    ~PostgresConnection();

private:
    PGconn* conn_ = nullptr;
};