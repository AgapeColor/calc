#pragma once

#include "context.h"

#include <string>
#include <optional>

struct OperationRecord {
    static OperationRecord fromContext(const Context& ctx);

    std::string operation_ = "";
    int arg1_ = 0;
    int arg2_ = 0;
    std::optional<int> result_;
    int status_ = 0;

private:
    static std::string convertOperation(Operation operation);
};
