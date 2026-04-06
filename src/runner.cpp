#include "runner.h"
#include "logger.h"

void Runner::run(int argc, char** argv) {
    Logger::instance().info("Application is started");

    parser_.parse_args(argc, argv, ctx_);
    checker_.check_args(ctx_);
    calculator_.calculate(ctx_);
    Printer::print_result(ctx_);

    Logger::instance().info("Application is finished");
}
