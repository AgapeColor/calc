#include "logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>

class Logger::Impl {
public:
    Impl() {
        std::filesystem::create_directories("logs");
        logger_ = spdlog::basic_logger_mt("file_logger", "logs/calc.log");
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::warn);
    }

    void info(const std::string& msg)   { logger_->info(msg); }
    void warn(const std::string& msg)   { logger_->warn(msg); }
    void error(const std::string& msg)  { logger_->error(msg); }
    void debug(const std::string& msg)  { logger_->debug(msg); }

private:
    std::shared_ptr<spdlog::logger> logger_;
};

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : impl_(std::make_unique<Impl>()) {}

Logger::~Logger() = default;

void Logger::info(const std::string& msg)   { impl_->info(msg); }
void Logger::warn(const std::string& msg)   { impl_->warn(msg); }
void Logger::error(const std::string& msg)  { impl_->error(msg); }
void Logger::debug(const std::string& msg)  { impl_->debug(msg); }

