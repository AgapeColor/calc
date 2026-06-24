#include "checker.h"
#include "context.h"
#include "logger.h"

#include <stdexcept>

void Checker::check_args(const Context& ctx) {
    Logger::instance().debug("Validating arguments");
    
    if (ctx.operation_ == Operation::NONE) {
        throw std::invalid_argument("OPERATION_NOT_SPECIFIED");
    }
    if (!ctx.hasA_) {
        throw std::invalid_argument("FIRST_ARGUMENT_MISSING");
    }
    if (!ctx.hasB_ && !isUnaryOperation(ctx.operation_)) {
        throw std::invalid_argument("SECOND_ARGUMENT_MISSING");
    }
}

bool Checker::isUnaryOperation(Operation operation) {
    return operation == Operation::FACT;
}
