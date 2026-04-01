#pragma once

#include "context.h"

class Parser {
public:
    void parse_args(int argc, char** argv, Context& ctx);
};