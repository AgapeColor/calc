#pragma once

#include "context.h"
#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"

class Runner {
public:
    Runner() = default;
    Runner(const Runner& obj) = default;
    Runner(Runner&& obj) = default;
    Runner& operator=(const Runner& obj) = default;
    Runner& operator=(Runner&& obj) = default;
    ~Runner() = default;

    void run(int argc, char** argv);

private:
    Context ctx_;
    Parser parser_;
};
