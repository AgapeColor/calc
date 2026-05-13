#include "calculator.h"
#include "calc_math.h"
#include "logger.h"

#include <stdexcept>

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
    ctx.mathCode_ = code;

    if (code != calc_math::OK) {
        Logger::instance().error(math_error_name(code));
        throw std::runtime_error(math_error_name(code));
    }
}

const char* Calculator::math_error_name(int errorCode) {
    switch (errorCode) {
        case calc_math::OVERFLOW:      return "Math error: overflow";
        case calc_math::DIV_BY_ZERO:   return "Math error: division by zero";
        case calc_math::INVALID_INPUT: return "Math error: invalid input";
        default:                       return "Math error: unknown";
    }
}
