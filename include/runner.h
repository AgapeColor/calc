#pragma once

class PostgresConnection;
class Cache;

class Runner {
public:
    Runner(PostgresConnection& dataBase, Cache& cache);
    Runner(const Runner& obj) = delete;
    Runner(Runner&& obj) = delete;
    Runner& operator=(const Runner& obj) = delete;
    Runner& operator=(Runner&& obj) = delete;
    ~Runner() = default;

    void run(int argc, char** argv);

private:
    PostgresConnection& dataBase_;
    Cache& cache_;
};
