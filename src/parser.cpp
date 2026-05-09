#include "parser.h"
#include "printer.h"
#include "logger.h"

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
    Logger::instance().debug("Parsing arguments");
    
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
        ctx.operation_ = parse_op(data);
        ctx.a_ = data.at("a").get<int>();
        ctx.hasA_ = true;
        if (ctx.operation_ != Operation::FACT) {
            ctx.b_ = data.at("b").get<int>();
            ctx.hasB_ = true;
        }
    }
    catch (const json::exception& e) {
        Logger::instance().error(std::string("JSON parse error: ") + e.what());
        throw std::invalid_argument(std::string("JSON parse error: ") + e.what());
    }
}
