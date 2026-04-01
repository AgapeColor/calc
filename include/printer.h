#pragma once

class Context;

class Printer {
public:
    static void print_result(const Context& ctx);
    static void print_help(const char* appName);
};