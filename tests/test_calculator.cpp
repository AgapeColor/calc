#include <gtest/gtest.h>
#include "context.h"
#include "calculator.h"

// Basic operations
TEST(CalculatorTest, AddTwoNumbers) {
    Context ctx;
    ctx.a_ = 5;
    ctx.b_ = 3;
    ctx.operation_ = Operation::ADD;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 8);
}
TEST(CalculatorTest, SubTwoNumbers) {
    Context ctx;
    ctx.a_ = 10;
    ctx.b_ = 4;
    ctx.operation_ = Operation::SUB;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 6);
}
TEST(CalculatorTest, MulTwoNumbers) {
    Context ctx;
    ctx.a_ = 6;
    ctx.b_ = 7;
    ctx.operation_ = Operation::MUL;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 42);
}
TEST(CalculatorTest, DivTwoNumbers) {
    Context ctx;
    ctx.a_ = 20;
    ctx.b_ = 4;
    ctx.operation_ = Operation::DIV;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 5);
}
TEST(CalculatorTest, PowOfNumber) {
    Context ctx;
    ctx.a_ = 2;
    ctx.b_ = 3;
    ctx.operation_ = Operation::POW;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 8);
}
TEST(CalculatorTest, FactOfNumber) {
    Context ctx;
    ctx.a_ = 5;
    ctx.operation_ = Operation::FACT;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 120);
}

// Factorial edge cases
TEST(CalculatorTest, FactOfZero) {
    Context ctx;
    ctx.a_ = 0;
    ctx.operation_ = Operation::FACT;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 1);
}
TEST(CalculatorTest, FactOfBigNum) {
    Context ctx;
    ctx.a_ = 15;
    ctx.operation_ = Operation::FACT;
    EXPECT_THROW(Calculator::calculate(ctx), std::exception);
}

// Power edge cases
TEST(CalculatorTest, ZeroPowOfZero) {
    Context ctx;
    ctx.a_ = 0;
    ctx.b_ = 0;
    ctx.operation_ = Operation::POW;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 1);
}
TEST(CalculatorTest, AnyPowOfZero) {
    Context ctx;
    ctx.a_ = 2657;
    ctx.b_ = 0;
    ctx.operation_ = Operation::POW;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 1);
}
TEST(CalculatorTest, ZeroPowOfAny) {
    Context ctx;
    ctx.a_ = 0;
    ctx.b_ = 395;
    ctx.operation_ = Operation::POW;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 0);
}

// Negative numbers
TEST(CalculatorTest, AddNegativeNums) {
    Context ctx;
    ctx.a_ = -5;
    ctx.b_ = -3;
    ctx.operation_ = Operation::ADD;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, -8);
}
TEST(CalculatorTest, SubWithNegativeResult) {
    Context ctx;
    ctx.a_ = 3;
    ctx.b_ = 10;
    ctx.operation_ = Operation::SUB;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, -7);
}
TEST(CalculatorTest, MulNegativeNums) {
    Context ctx;
    ctx.a_ = -5;
    ctx.b_ = -3;
    ctx.operation_ = Operation::MUL;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 15);
}
TEST(CalculatorTest, DivNegativeNums) {
    Context ctx;
    ctx.a_ = -20;
    ctx.b_ = -4;
    ctx.operation_ = Operation::DIV;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 5);
}

// Operations with zero
TEST(CalculatorTest, MulByZero) {
    Context ctx;
    ctx.a_ = 5;
    ctx.b_ = 0;
    ctx.operation_ = Operation::MUL;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 0);
}
TEST(CalculatorTest, DivZero) {
    Context ctx;
    ctx.a_ = 0;
    ctx.b_ = 5;
    ctx.operation_ = Operation::DIV;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 0);
}

// Integer division
TEST(CalculatorTest, IntegerDivWithRemainder) {
    Context ctx;
    ctx.a_ = 7;
    ctx.b_ = 2;
    ctx.operation_ = Operation::DIV;
    Calculator::calculate(ctx);
    EXPECT_EQ(ctx.result_, 3);
}

// Overflow 
TEST(CalculatorTest, PowOverflow) {
    Context ctx;
    ctx.a_ = 2;
    ctx.b_ = 31;
    ctx.operation_ = Operation::POW;
    EXPECT_THROW(Calculator::calculate(ctx), std::exception);
}
