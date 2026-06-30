#include "response_serializer.h"

#include "context.h"

#include <nlohmann/json.hpp>

std::string ResponseSerializer::resultToJson(const Context& ctx) {
    nlohmann::json response;

    response["result"] = ctx.result_;

    return response.dump();
}

std::string ResponseSerializer::errorToJson(std::string type, std::string code) {
    nlohmann::json response;

    response["error"]["type"] = type;
    response["error"]["code"] = code;

    return response.dump();
}
