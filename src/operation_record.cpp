#include "operation_record.h"
#include "postgres_result.h"
#include "sql.h"

#include <stdexcept>

OperationRecord OperationRecord::fromContext(const Context& ctx) {
    OperationRecord record;
    record.operation_ = operationToString(ctx.operation_);
    record.arg1_ = ctx.a_;
    record.arg2_ = ctx.hasB_ ? std::optional<int>(ctx.b_) : std::nullopt;

    if (ctx.hasB_ && (record.operation_ == "add" || record.operation_ == "mul") && ctx.a_ > ctx.b_) {
        record.arg1_ = ctx.b_;
        record.arg2_ = ctx.a_;
    }

    record.result_ = (ctx.mathCode_ != 0) // 0 = success (MathCode::OK)
        ? std::nullopt
        : std::optional<int>(ctx.result_);

    record.status_ = ctx.mathCode_;
    
    return record;
}

OperationRecord OperationRecord::fromDatabase(const PostgresResult& result, int row) {
    OperationRecord record;
    record.operation_ = result.cellValue(row, SqlColumns::Operation);
    record.arg1_ = std::stoi(result.cellValue(row, SqlColumns::Arg1));
    record.arg2_ = result.isNull(row, SqlColumns::Arg2)
        ? std::nullopt
        : std::optional<int>(std::stoi(result.cellValue(row, SqlColumns::Arg2)));
    record.result_ = result.isNull(row, SqlColumns::Result)
        ? std::nullopt
        : std::optional<int>(std::stoi(result.cellValue(row, SqlColumns::Result)));
    record.status_ = std::stoi(result.cellValue(row, SqlColumns::Status));
    return record;
}

Context OperationRecord::toContext() const {
    Context ctx;
    ctx.operation_ = stringToOperation(operation_);
    ctx.a_ = arg1_;
    ctx.hasA_ = true;
    ctx.b_ = arg2_.value_or(0);
    ctx.hasB_ = arg2_.has_value();
    ctx.result_ = result_.value_or(0);
    ctx.mathCode_ = status_;
    return ctx;
}

std::string OperationRecord::operationToString(Operation operation)  {
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

Operation OperationRecord::stringToOperation(const std::string& operation) {
    if (operation == "add")  return Operation::ADD;
    if (operation == "sub")  return Operation::SUB;
    if (operation == "mul")  return Operation::MUL;
    if (operation == "div")  return Operation::DIV;
    if (operation == "pow")  return Operation::POW;
    if (operation == "fact") return Operation::FACT;
    if (operation.empty())   return Operation::NONE;

    throw std::logic_error("Unknown operation: " + operation);
}
