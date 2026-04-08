#pragma once

#include "context.h"

class Calculator {
public:
    Calculator() = default;
    Calculator(const Calculator& obj) = default;
    Calculator(Calculator&& obj) = default;
    Calculator& operator=(const Calculator& obj) = default;
    Calculator& operator=(Calculator&& obj) = default;
    ~Calculator() = default;

    static void calculate(Context& ctx);
private:
    static const char* math_error_name(int errorCode);
};