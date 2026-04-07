#pragma once

#include "context.h"
#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"

class Runner {
public:
    void run(int argc, char** argv);

private:
    Context ctx_;
    Parser parser_;
};
