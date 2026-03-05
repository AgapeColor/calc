#include "runner.h"
#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"

AppCode run(int argc, char** argv) {
    Context ctx;

    if (parse_args(argc, argv, ctx) != 0)
        return BAD_ARGS;

    if (check_args(ctx) != 0) {
        print_result(ctx);
        return CHECK_FAILED;
    }

    if (calculate(ctx) != 0) {
        print_result(ctx);
        return CALC_FAILED;
    }

    print_result(ctx);
    
    return OK;
}
