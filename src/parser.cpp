#include "parser.h"
#include "logger.h"
#include "app_error.h"

#include <nlohmann/json.hpp>

#include <string>

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

void Parser::parse_json(const std::string& rawJson, Context& ctx) {
    if (rawJson.empty()) {
        throw RequestError("JSON_ARGUMENT_MISSED");
    }

    Logger::instance().debug("Parsing JSON request");

    using json = nlohmann::json;
    try {
        json data = json::parse(rawJson.c_str());
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
        throw RequestError("JSON_PARSE_ERROR");
    }
}
