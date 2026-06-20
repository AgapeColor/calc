#pragma once

#include "context.h"

#include <string>

class Parser {
public:
    Parser() = default;
    Parser(const Parser& obj) = default;
    Parser(Parser&& obj) = default;
    Parser& operator=(const Parser& obj) = default;
    Parser& operator=(Parser&& obj) = default;
    ~Parser() = default;

    void parse_json(const std::string& rawJson, Context& ctx);
};
