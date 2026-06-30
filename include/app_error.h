#pragma once

#include <stdexcept>

class RequestError : public std::invalid_argument {
public:
    using std::invalid_argument::invalid_argument;
};

class MathError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};