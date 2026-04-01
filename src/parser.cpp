#include "parser.h"
#include "printer.h"

#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>

static Operation parse_op(const nlohmann::json& data) {
    if (!data.contains("op")) {
        return Operation::NONE;
    }
    std::string oper = data.at("op").get<std::string>();
    if (oper == "add")  return Operation::ADD;
    if (oper == "sub")  return Operation::SUB;
    if (oper == "mul")  return Operation::MUL;
    if (oper == "div")  return Operation::DIV;
    if (oper == "pow")  return Operation::POW;
    if (oper == "fact") return Operation::FACT;
    return Operation::NONE;
}

void Parser::parse_args(int argc, char** argv, Context& ctx) {
    using json = nlohmann::json;

    if (argc < 2) {
        throw std::invalid_argument("JSON argument is missed");
    }
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
        Printer::print_help(argv[0]);
        exit(0);
    }
    try {
        json data = json::parse(argv[1]);
        ctx.setOperation(parse_op(data));
        ctx.setA(data.at("a").get<int>());
        if (ctx.getOperation() != Operation::FACT)
            ctx.setB(data.at("b").get<int>());
    }
    catch (const json::exception& e) {
        throw std::invalid_argument(std::string("JSON parse error: ") + e.what());
    }
}