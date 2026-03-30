#include "runner.h"

void Runner::run(int argc, char** argv) {
    parser_.parse_args(argc, argv, ctx_);
    checker_.check_args(ctx_);
    calculator_.calculate(ctx_);
    printer_.print_result(ctx_);
}
