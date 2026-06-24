#pragma once

#include <string>

struct Context;

class ResponseSerializer {
public:
    static std::string resultToJson(const Context& ctx);
    static std::string errorToJson(std::string type, std::string code);
};
