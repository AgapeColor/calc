#pragma once

#include "context.h"

class Calculator {
public:
    void calculate(Context& ctx);
private:
    static const char* math_error_name(int errorCode);
};