#include "checker.h"

int check_args(Context& ctx) {

    if (ctx.operation == NONE) { ctx.app_code = BAD_ARGS; return 1; }

    if (!ctx.has_a) { ctx.app_code = BAD_ARGS; return 1; }
    
    if (!ctx.has_b && ctx.operation != FACT) { ctx.app_code = BAD_ARGS; return 1; }

    if (ctx.operation == POW && ctx.b < 0)   { ctx.app_code = CHECK_FAILED; return 1; }
    if (ctx.operation == FACT && ctx.a < 0)  { ctx.app_code = CHECK_FAILED; return 1; }
    if (ctx.operation == DIV && ctx.b == 0)  { ctx.app_code = CHECK_FAILED; return 1; }

    ctx.app_code = OK;
    return 0;
}
