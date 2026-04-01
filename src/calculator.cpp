#include "calculator.h"
#include "calc_math.h"

#include <stdexcept>

void Calculator::calculate(Context& ctx) {
    calc_math::MathCode code = calc_math::OK;
    int result = 0;
    switch (ctx.getOperation()) {
        case Operation::ADD:
            code = calc_math::add(ctx.getA(), ctx.getB(), result);
            break;        
        case Operation::SUB:
            code = calc_math::sub(ctx.getA(), ctx.getB(), result);
            break;
        case Operation::MUL:
            code = calc_math::mul(ctx.getA(), ctx.getB(), result);
            break;
        case Operation::DIV:
            code = calc_math::div(ctx.getA(), ctx.getB(), result);
            break;
        case Operation::POW:
            code = calc_math::pow(ctx.getA(), ctx.getB(), result);
            break;
        case Operation::FACT:
            code = calc_math::fact(ctx.getA(), result);
            break;
        default: break;
    }
    
    ctx.setResult(result);

    if (code != calc_math::OK) {
        throw std::runtime_error(math_error_name(code));
    }
}

const char* Calculator::math_error_name(int errorCode) {
    switch (errorCode) {
        case calc_math::OVERFLOW:      return "Math error: overflow";
        case calc_math::DIV_BY_ZERO:   return "Math error: division by zero";
        case calc_math::INVALID_INPUT: return "Math error: invalid input";
        default:                       return "Math error: none";
    }
}