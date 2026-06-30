#include <gtest/gtest.h>
#include <exception>
#include <string>
#include "context.h"
#include "parser.h"

// JSON tests
TEST(ParserTest, missedJson) {
    Context ctx;
    Parser parser;
    std::string json;
    EXPECT_THROW(parser.parse_json(json, ctx), std::exception);
}
TEST(ParserTest, invalidJson) {
    Context ctx;
    Parser parser;
    std::string json = "not a json";
    EXPECT_THROW(parser.parse_json(json, ctx), std::exception);
}

// Operation tests
TEST(ParserTest, missedOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"a\":5,\"b\":3}";
    EXPECT_NO_THROW(parser.parse_json(json, ctx));
    EXPECT_EQ(ctx.operation_, Operation::NONE);
}
TEST(ParserTest, unknownOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"unknown\",\"a\":5,\"b\":3}";
    EXPECT_NO_THROW(parser.parse_json(json, ctx));
    EXPECT_EQ(ctx.operation_, Operation::NONE);
}
TEST(ParserTest, validAddOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"add\",\"a\":5,\"b\":3}";
    parser.parse_json(json, ctx);
    EXPECT_EQ(ctx.operation_, Operation::ADD);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validSubOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"sub\",\"a\":5,\"b\":3}";
    parser.parse_json(json, ctx);
    EXPECT_EQ(ctx.operation_, Operation::SUB);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validMulOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"mul\",\"a\":5,\"b\":3}";
    parser.parse_json(json, ctx);
    EXPECT_EQ(ctx.operation_, Operation::MUL);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validDivOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"div\",\"a\":5,\"b\":3}";
    parser.parse_json(json, ctx);
    EXPECT_EQ(ctx.operation_, Operation::DIV);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validPowOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"pow\",\"a\":5,\"b\":3}";
    parser.parse_json(json, ctx);
    EXPECT_EQ(ctx.operation_, Operation::POW);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validFactOperation) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"fact\",\"a\":5}";
    parser.parse_json(json, ctx);
    EXPECT_EQ(ctx.operation_, Operation::FACT);
    EXPECT_EQ(ctx.a_, 5);
}

// Argument tests
TEST(ParserTest, missedFirstArg) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"add\",\"b\":3}";
    EXPECT_THROW(parser.parse_json(json, ctx), std::exception);
}
TEST(ParserTest, missedSecondArg) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"add\",\"a\":5}";
    EXPECT_THROW(parser.parse_json(json, ctx), std::exception);
}
TEST(ParserTest, factorialWithoutSecondArg) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"fact\",\"a\":5}";
    EXPECT_NO_THROW(parser.parse_json(json, ctx));
}
TEST(ParserTest, nonNumFirstArg) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"div\",\"a\":\"str\",\"b\":3}";
    EXPECT_THROW(parser.parse_json(json, ctx), std::exception);
}
TEST(ParserTest, nonNumSecondArg) {
    Context ctx;
    Parser parser;
    std::string json = "{\"op\":\"div\",\"a\":5,\"b\":\"str\"}";
    EXPECT_THROW(parser.parse_json(json, ctx), std::exception);
}
