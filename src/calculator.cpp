#include "calculator.h"

#include "calc_math.h"
#include "logger.h"
#include "app_error.h"

void Calculator::calculate(Context& ctx) {
    Logger::instance().debug("Calculating result");
    
    calc_math::MathCode code = calc_math::OK;
    int result = 0;
    switch (ctx.operation_) {
        case Operation::ADD:
            code = calc_math::add(ctx.a_, ctx.b_, result);
            break;        
        case Operation::SUB:
            code = calc_math::sub(ctx.a_, ctx.b_, result);
            break;
        case Operation::MUL:
            code = calc_math::mul(ctx.a_, ctx.b_, result);
            break;
        case Operation::DIV:
            code = calc_math::div(ctx.a_, ctx.b_, result);
            break;
        case Operation::POW:
            code = calc_math::pow(ctx.a_, ctx.b_, result);
            break;
        case Operation::FACT:
            code = calc_math::fact(ctx.a_, result);
            break;
        default: break;
    }
    
    ctx.result_ = result;
    ctx.mathCode_ = static_cast<int>(code);

    if (code != calc_math::OK) {
        Logger::instance().error(math_error_name(code));
        throw MathError(math_error_name(code));
    }
}

const char* Calculator::math_error_name(int errorCode) {
    switch (errorCode) {
        case calc_math::OVERFLOW:      return "OVERFLOW";
        case calc_math::DIV_BY_ZERO:   return "DIV_BY_ZERO";
        case calc_math::INVALID_INPUT: return "INVALID_INPUT";
        default:                       return "UNKNOWN_MATH_ERROR";
    }
}
