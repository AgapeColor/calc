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
    void setOperation(Operation value) { operation = value; }
    void setA(int value) { a = value; has_a = true; }
    void setB(int value) { b = value; has_b = true; }
    void setResult(int value) { result = value; }

    // Getters
    Operation getOperation() const { return operation; }
    int getA() const { return a; }
    int getB() const { return b; }
    bool hasA() const { return has_a; }
    bool hasB() const { return has_b; }
    int getResult() const { return result; }

private:
    Operation operation = Operation::NONE;
    int a = 0;
    int b = 0;
    bool has_a = false;
    bool has_b = false;
    int result = 0;
};