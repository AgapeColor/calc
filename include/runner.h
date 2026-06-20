#pragma once

#include "context.h"
#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"
#include "cache.h"
#include "postgres_connection.h"

class Runner {
public:
    Runner(PostgresConnection& dataBase, Cache& cache);
    Runner(const Runner& obj) = default;
    Runner(Runner&& obj) = default;
    Runner& operator=(const Runner& obj) = default;
    Runner& operator=(Runner&& obj) = default;
    ~Runner() = default;

    void run(int argc, char** argv);

private:
    Context ctx_;
    Parser parser_;
    PostgresConnection& dataBase_;
    Cache& cache_;
};