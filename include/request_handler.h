#pragma once

#include "parser.h"

#include <string>

class PostgresConnection;
class Cache;
struct Context;

class RequestHandler {
public:
    RequestHandler(PostgresConnection& dataBase, Cache& cache);

    RequestHandler(const RequestHandler& obj) = delete;
    RequestHandler(RequestHandler&& obj) = delete;
    RequestHandler& operator=(const RequestHandler& obj) = delete;
    RequestHandler& operator=(RequestHandler&& obj) = delete;

    ~RequestHandler() = default;

    Context handle(const std::string& rawRequest);

private:
    Parser parser_;
    PostgresConnection& dataBase_;
    Cache& cache_;

};
