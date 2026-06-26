#pragma once

#include <csignal>
#include <future>

class PostgresConnection;
class Cache;
class TcpServer;

class Application {
public:
    Application(PostgresConnection& dataBase, Cache& cache);
    Application(const Application& obj) = delete;
    Application(Application&& obj) = delete;
    Application& operator=(const Application& obj) = delete;
    Application& operator=(Application&& obj) = delete;
    ~Application() = default;

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
