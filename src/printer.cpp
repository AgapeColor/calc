#include "printer.h"
#include "calc_math.h"

#include <stdio.h>

static const char* math_error_name(int errorCode) {
    switch (errorCode) {
        case calc_math::OVERFLOW:      return "overflow";
        case calc_math::DIV_BY_ZERO:   return "division by zero";
        case calc_math::INVALID_INPUT: return "invalid input";
        default:                       return "none";
    }
}

void print_result(Context& ctx) {
    if (ctx.app_code != OK) {
        printf("Error: bad input or check failed (app_code: %d)\n", ctx.app_code);
        return;
    }
    if (ctx.math_code != calc_math::OK) {
        printf("Math error: %s (code=%d)\n", math_error_name(ctx.math_code), ctx.math_code);
        return;
    }

    printf("Result: %d\n", ctx.result);
}
