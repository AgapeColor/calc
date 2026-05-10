#pragma once

#include "context.h"

#include <string>
#include <optional>

class PostgresResult;

struct OperationRecord {
    static OperationRecord fromContext(const Context& ctx);

    static OperationRecord fromDatabase(const PostgresResult& result, int row);

    std::string operation_ = "";
    int arg1_ = 0;
    std::optional<int> arg2_;
    std::optional<int> result_;
    int status_ = 0;

private:
    static std::string convertOperation(Operation operation);
};
