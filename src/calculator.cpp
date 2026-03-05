#include "calculator.h"
#include "calc_math.h"

int calculate(Context& ctx) {
    calc_math::MathCode code = calc_math::OK;

    switch (ctx.operation){
        case ADD:  code = calc_math::add(ctx.a, ctx.b, ctx.result); break;
        case SUB:  code = calc_math::sub(ctx.a, ctx.b, ctx.result); break;
        case MUL:  code = calc_math::mul(ctx.a, ctx.b, ctx.result); break;
        case DIV:  code = calc_math::div(ctx.a, ctx.b, ctx.result); break;
        case POW:  code = calc_math::pow(ctx.a, ctx.b, ctx.result); break;
        case FACT: code = calc_math::fact(ctx.a, ctx.result);       break;
        default: return 1;
    }

    ctx.math_code = code;
    return (code == calc_math::OK) ? 0 : 1;
}
