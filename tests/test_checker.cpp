#include <gtest/gtest.h>
#include <exception>
#include "checker.h"
#include "context.h"

// Operation tests
TEST(CheckerTest, missedOperation) {
    Context ctx;
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}

// Argument tests
TEST(CheckerTest, missedFirstArg) {
    Context ctx;
    ctx.operation_ = Operation::ADD;
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, missedSecondArg) {
    Context ctx;
    ctx.operation_ = Operation::ADD;
    ctx.a_ = 5;
    ctx.hasA_ = true;
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}

// Specific operation rules
TEST(CheckerTest, negativeExponent) {
    Context ctx;
    ctx.operation_ = Operation::POW;
    ctx.a_ = 2;
    ctx.b_ = -3;
    ctx.hasA_ = true;
    ctx.hasB_ = true;
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, zeroExponent) {
    Context ctx;
    ctx.operation_ = Operation::POW;
    ctx.a_ = 2;
    ctx.b_ = 0;
    ctx.hasA_ = true;
    ctx.hasB_ = true;
    EXPECT_NO_THROW(Checker::check_args(ctx));
}
TEST(CheckerTest, negativeFact) {
    Context ctx;
    ctx.operation_ = Operation::FACT;
    ctx.a_ = -5;
    ctx.hasA_ = true;
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, validFact) {
    Context ctx;
    ctx.operation_ = Operation::FACT;
    ctx.a_ = 5;
    ctx.hasA_ = true;
    EXPECT_NO_THROW(Checker::check_args(ctx));
}
TEST(CheckerTest, divisionByZero) {
    Context ctx;
    ctx.operation_ = Operation::DIV;
    ctx.a_ = 10;
    ctx.b_ = 0;
    ctx.hasA_ = true;
    ctx.hasB_ = true;
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, negativeDivision) {
    Context ctx;
    ctx.operation_ = Operation::DIV;
    ctx.a_ = -10;
    ctx.b_ = 2;
    ctx.hasA_ = true;
    ctx.hasB_ = true;
    EXPECT_NO_THROW(Checker::check_args(ctx));
}
