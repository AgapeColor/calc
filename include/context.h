#pragma once

enum class Operation {
    NONE = 0,
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    FACT
};

struct Context {
    Context() = default;
    Context(const Context& obj) = default;
    Context(Context&& obj) = default;
    Context& operator=(const Context& obj) = default;
    Context& operator=(Context&& obj) = default;
    ~Context() = default;

    Operation operation_ = Operation::NONE;
    int a_ = 0;
    int b_ = 0;
    bool hasA_ = false;
    bool hasB_ = false;
    int result_ = 0;
};