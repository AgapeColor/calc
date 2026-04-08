#include "checker.h"
#include "context.h"
#include "logger.h"

#include <stdexcept>

void Checker::check_args(const Context& ctx) {
    Logger::instance().debug("Validating arguments");
    
    if (ctx.operation_ == Operation::NONE) {
        throw std::invalid_argument("operation is not specified");
    }
    if (!ctx.hasA_) {
        throw std::invalid_argument("first argument is missing");
    }
    if (!ctx.hasB_ && ctx.operation_ != Operation::FACT) {
        throw std::invalid_argument("second argument is missing");
    }

    switch (ctx.operation_) {
        case Operation::POW:
            if(ctx.b_ < 0) {
                throw std::invalid_argument("power exponent must be non-negative");
            }
            break;
        case Operation::FACT:
            if(ctx.a_ < 0) {
                throw std::invalid_argument("factorial argument must be non-negative");
            }
            break;
        case Operation::DIV:
            if(ctx.b_ == 0) {
                throw std::invalid_argument("division by zero is not allowed");
            }
            break;
        
        default:
            break;
    }
}
