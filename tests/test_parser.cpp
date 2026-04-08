#include <gtest/gtest.h>
#include <exception>
#include "context.h"
#include "parser.h"

// JSON tests
TEST(ParserTest, missedJson) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char* argv[] = {argv0};
    EXPECT_THROW(parser.parse_args(1, argv, ctx), std::exception);
}
TEST(ParserTest, invalidJson) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "not a json";
    char* argv[] = {argv0, argv1};
    EXPECT_THROW(parser.parse_args(2, argv, ctx), std::exception);
}

// Operation tests
TEST(ParserTest, missedOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::NONE);
}
TEST(ParserTest, unknownOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"unknown\",\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    EXPECT_NO_THROW(parser.parse_args(2, argv, ctx));
    EXPECT_EQ(ctx.operation_, Operation::NONE);
}
TEST(ParserTest, validAddOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"add\",\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::ADD);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validSubOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"sub\",\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::SUB);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validMulOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"mul\",\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::MUL);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validDivOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"div\",\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::DIV);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validPowOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"pow\",\"a\":5,\"b\":3}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::POW);
    EXPECT_EQ(ctx.a_, 5);
    EXPECT_EQ(ctx.b_, 3);
}
TEST(ParserTest, validFactOperation) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"fact\",\"a\":5}";
    char* argv[] = {argv0, argv1};
    parser.parse_args(2, argv, ctx);
    EXPECT_EQ(ctx.operation_, Operation::FACT);
    EXPECT_EQ(ctx.a_, 5);
}

// Argument tests
TEST(ParserTest, missedFirstArg) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"add\",\"b\":3}";
    char* argv[] = {argv0, argv1};
    EXPECT_THROW(parser.parse_args(2, argv, ctx), std::exception);
}
TEST(ParserTest, missedSecondArg) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"add\",\"a\":5}";
    char* argv[] = {argv0, argv1};
    EXPECT_THROW(parser.parse_args(2, argv, ctx), std::exception);
}
TEST(ParserTest, factorialWithoutSecondArg) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"fact\",\"a\":5}";
    char* argv[] = {argv0, argv1};
    EXPECT_NO_THROW(parser.parse_args(2, argv, ctx));
}
TEST(ParserTest, nonNumFirstArg) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"div\",\"a\":\"str\",\"b\":3}";
    char* argv[] = {argv0, argv1};
    EXPECT_THROW(parser.parse_args(2, argv, ctx), std::exception);
}
TEST(ParserTest, nonNumSecondArg) {
    Context ctx;
    Parser parser;
    char argv0[] = "calc";
    char argv1[] = "{\"op\":\"div\",\"a\":5,\"b\":\"str\"}";
    char* argv[] = {argv0, argv1};
    EXPECT_THROW(parser.parse_args(2, argv, ctx), std::exception);
}
