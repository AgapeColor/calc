#pragma once

struct Context;
enum class Operation;

class Checker {
public:
    Checker() = default;
    Checker(const Checker& obj) = default;
    Checker(Checker&& obj) = default;
    Checker& operator=(const Checker& obj) = default;
    Checker& operator=(Checker&& obj) = default;
    ~Checker() = default;
    
    static void check_args(const Context& ctx);
private:
    static bool isUnaryOperation(Operation operation);
};
