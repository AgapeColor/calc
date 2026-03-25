#pragma once

enum Operation {
    NONE = 0,
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    FACT
};

enum AppCode {
    OK = 0,
    BAD_ARGS = 7,
    CHECK_FAILED = 8,
    CALC_FAILED = 9
};

struct Context {
    Operation operation = NONE;

    int a = 0;
    int b = 0;
    
    bool has_a = false;
    bool has_b = false;
    
    int result = 0;
    
    AppCode app_code = OK;
    int math_code = 0;
};
