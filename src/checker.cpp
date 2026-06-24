#include "checker.h"

#include "context.h"
#include "logger.h"
#include "app_error.h"

void Checker::check_args(const Context& ctx) {
    Logger::instance().debug("Validating arguments");
    
    if (ctx.operation_ == Operation::NONE) {
        throw RequestError("OPERATION_NOT_SPECIFIED");
    }
    if (!ctx.hasA_) {
        throw RequestError("FIRST_ARGUMENT_MISSING");
    }
    if (!ctx.hasB_ && !isUnaryOperation(ctx.operation_)) {
        throw RequestError("SECOND_ARGUMENT_MISSING");
    }
}

bool Checker::isUnaryOperation(Operation operation) {
    return operation == Operation::FACT;
}
