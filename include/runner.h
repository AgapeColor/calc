#pragma once

#include <csignal>
#include <future>

class PostgresConnection;
class Cache;
class TcpServer;

class Runner {
public:
    Runner(PostgresConnection& dataBase, Cache& cache);
    Runner(const Runner& obj) = delete;
    Runner(Runner&& obj) = delete;
    Runner& operator=(const Runner& obj) = delete;
    Runner& operator=(Runner&& obj) = delete;
    ~Runner() = default;

    void run();

private:
    static sigset_t createShutdownSignalSet();
    static void blockSignals(const sigset_t& signalSet);
    static void waitForShutdownSignal(
        TcpServer& server,
        const sigset_t& signalSet,
        std::future<void>& serverFuture
    );

    PostgresConnection& dataBase_;
    Cache& cache_;
};
