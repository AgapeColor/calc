#pragma once

struct Context;

class Printer {
public:
    Printer() = default;
    Printer(const Printer& obj) = default;
    Printer(Printer&& obj) = default;
    Printer& operator=(const Printer& obj) = default;
    Printer& operator=(Printer&& obj) = default;
    ~Printer() = default;

    static void print_result(const Context& ctx);
    static void print_help(const char* appName);
};