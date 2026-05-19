#pragma once

#include "context.h"

class Parser {
public:
    Parser() = default;
    Parser(const Parser& obj) = default;
    Parser(Parser&& obj) = default;
    Parser& operator=(const Parser& obj) = default;
    Parser& operator=(Parser&& obj) = default;
    ~Parser() = default;

    void parse_args(int argc, char** argv, Context& ctx);
};
