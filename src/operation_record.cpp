#include "operation_record.h"

#include <stdexcept>

OperationRecord OperationRecord::fromContext(const Context& ctx) {
    OperationRecord record;
    record.operation_ = convertOperation(ctx.operation_);
    record.arg1_ = ctx.a_;
    record.arg2_ = ctx.b_;
    record.result_ = (ctx.mathCode_ != 0) // 0 = success (MathCode::OK)
        ? std::nullopt
        : std::optional<int>(ctx.result_);

    record.status_ = ctx.mathCode_;
    
    return record;
}

std::string OperationRecord::convertOperation(Operation operation)  {
    switch (operation) {
        case Operation::ADD:    return std::string("add");
        case Operation::SUB:    return std::string("sub");
        case Operation::MUL:    return std::string("mul");
        case Operation::DIV:    return std::string("div");
        case Operation::POW:    return std::string("pow");
        case Operation::FACT:   return std::string("fact");
        case Operation::NONE:   return std::string("");
        
        default:
            throw std::logic_error("Unknown operation: " + std::to_string(static_cast<int>(operation)));
    }
}
