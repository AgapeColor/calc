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
    ctx.setOperation(Operation::ADD);
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, missedSecondArg) {
    Context ctx;
    ctx.setOperation(Operation::ADD);
    ctx.setA(5);
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}

// Specific operation rules
TEST(CheckerTest, negativeExponent) {
    Context ctx;
    ctx.setOperation(Operation::POW);
    ctx.setA(2);
    ctx.setB(-3);
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, zeroExponent) {
    Context ctx;
    ctx.setOperation(Operation::POW);
    ctx.setA(2);
    ctx.setB(0);
    EXPECT_NO_THROW(Checker::check_args(ctx));
}
TEST(CheckerTest, negativeFact) {
    Context ctx;
    ctx.setOperation(Operation::FACT);
    ctx.setA(-5);
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, validFact) {
    Context ctx;
    ctx.setOperation(Operation::FACT);
    ctx.setA(5);
    EXPECT_NO_THROW(Checker::check_args(ctx));
}
TEST(CheckerTest, divisionByZero) {
    Context ctx;
    ctx.setOperation(Operation::DIV);
    ctx.setA(10);
    ctx.setB(0);
    EXPECT_THROW(Checker::check_args(ctx), std::invalid_argument);
}
TEST(CheckerTest, negativeDivision) {
    Context ctx;
    ctx.setOperation(Operation::DIV);
    ctx.setA(-10);
    ctx.setB(2);
    EXPECT_NO_THROW(Checker::check_args(ctx));
}
