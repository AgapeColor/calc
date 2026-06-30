#include "application.h"

#include "cache.h"
#include "request_handler.h"
#include "tcp_server.h"
#include "logger.h"

#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <exception>
#include <functional>
#include <future>
#include <stdexcept>
#include <string>
#include <thread>

#include <pthread.h>

Application::Application(PostgresConnection& dataBase, Cache& cache) 
    : dataBase_(dataBase),
      cache_(cache)
{}

void Application::run() {

    constexpr std::uint16_t serverPort = 8080;

    RequestHandler handler(dataBase_, cache_);

    TcpServer server(serverPort, handler);

    sigset_t signalSet = createShutdownSignalSet();
    blockSignals(signalSet);

    std::promise<void> serverPromise;
    std::future<void> serverFuture = serverPromise.get_future();

    std::thread signalThread(
        &Application::waitForShutdownSignal,
        std::ref(server),
        std::cref(signalSet),
        std::ref(serverFuture)
    );

    std::thread serverThread([&server, &serverPromise]() {
        try {
            server.run();
            serverPromise.set_value();
        }
        catch (...) {
            serverPromise.set_exception(std::current_exception());
        }
    });

    signalThread.join();
    serverThread.join();

    serverFuture.get();
}

sigset_t Application::createShutdownSignalSet() {
    sigset_t signalSet;

    if (sigemptyset(&signalSet) != 0 ||
        sigaddset(&signalSet, SIGINT) != 0 ||
        sigaddset(&signalSet, SIGTERM) != 0) {
        Logger::instance().error("Failed to configure shutdown signal set");
        throw std::runtime_error("Failed to configure shutdown signal set");
    }

    return signalSet;
}

void Application::blockSignals(const sigset_t& signalSet) {
    int maskResult = pthread_sigmask(SIG_BLOCK, &signalSet, nullptr);

    if (maskResult != 0) {
        Logger::instance().error("Failed to block shutdown signals");
        throw std::runtime_error("Failed to block shutdown signals");
    }
}

void Application::waitForShutdownSignal(TcpServer& server,
                                   const sigset_t& signalSet,
                                   std::future<void>& serverFuture) {
    siginfo_t signalInfo {};
    timespec timeout;
    timeout.tv_sec = 0;
    timeout.tv_nsec = 100'000'000;

    while (serverFuture.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
        int receivedSignal = sigtimedwait(&signalSet, &signalInfo, &timeout);
        if (receivedSignal == SIGINT || receivedSignal == SIGTERM) {
            Logger::instance().info("Received shutdown signal: " + std::to_string(receivedSignal));
            server.requestStop();
            break;
        }
        if (receivedSignal == -1) {
            if (errno == EAGAIN) {
                continue;
            }
            Logger::instance().error("Failed to wait shutdown signal");
            server.requestStop();
            break;
        }
    }
}
