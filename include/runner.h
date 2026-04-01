#pragma once

#include "context.h"
#include "parser.h"
#include "checker.h"
#include "calculator.h"

class Runner {
public:
    void run(int argc, char** argv);

private:
    Context ctx_;
    Parser parser_;
    Checker checker_;
    Calculator calculator_;
};
