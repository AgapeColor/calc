#include "runner.h"

void Runner::run(int argc, char** argv) {
    parser_.parse_args(argc, argv, ctx_);
    Checker::check_args(ctx_);
    Calculator::calculate(ctx_);
    Printer::print_result(ctx_);
}
