#pragma once

#include <string>
#include <memory>

class Logger {
public:
    static Logger& instance();

    Logger(const Logger& obj) = delete;
    Logger& operator=(const Logger& obj) = delete;
    Logger(Logger&& obj) = delete;
    Logger& operator=(Logger&& obj) = delete;

    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
    void debug(const std::string& msg);

private:
    Logger();
    ~Logger();

    class Impl;
    std::unique_ptr<Impl> impl_;
};
