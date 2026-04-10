#include "printer.h"
#include "context.h"

#include <iostream>

void Printer::print_result(const Context& ctx) {
    std::cout << "Result: " << ctx.result_ << std::endl;
}

void Printer::print_help(const char* appName) {
    using namespace std;

    cout << "Usage:"                                                 << endl;
    cout << "  " << appName << " '{\"op\":\"add\",\"a\":2,\"b\":3}'" << endl;
    cout << "  " << appName << " '{\"op\":\"fact\",\"a\":5}'"        << endl;

    cout << "\nJSON format:"                                 << endl;
    cout << "  op  - operation: add|sub|mul|div|pow|fact"    << endl;
    cout << "  a   - first integer"                          << endl;
    cout << "  b   - second integer (not required for fact)" << endl;
    
    cout << "\nExamples:"                           << endl;
    cout << "  '{\"op\":\"sub\",\"a\":10,\"b\":5}'" << endl;
    cout << "  '{\"op\":\"pow\",\"a\":2,\"b\":8}'"  << endl;
    cout << "  '{\"op\":\"fact\",\"a\":5}'"         << endl;
}
