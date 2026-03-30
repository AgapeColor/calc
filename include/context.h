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

class Context {
public:
    // Setters
    void setOperation(Operation value) { operation_ = value; }
    void setA(int value) { a_ = value; has_a_ = true; }
    void setB(int value) { b_ = value; has_b_ = true; }
    void setResult(int value) { result_ = value; }

    // Getters
    Operation getOperation() const { return operation_; }
    int getA() const { return a_; }
    int getB() const { return b_; }
    bool hasA() const { return has_a_; }
    bool hasB() const { return has_b_; }
    int getResult() const { return result_; }

private:
    Operation operation_ = Operation::NONE;
    int a_ = 0;
    int b_ = 0;
    bool has_a_ = false;
    bool has_b_ = false;
    int result_ = 0;
};