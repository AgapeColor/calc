#include <gtest/gtest.h>
#include "context.h"
#include "calculator.h"

// Basic operations
TEST(CalculatorTest, AddTwoNumbers) {
    Context ctx;
    ctx.setA(5);
    ctx.setB(3);
    ctx.setOperation(Operation::ADD);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 8);
}
TEST(CalculatorTest, SubTwoNumbers) {
    Context ctx;
    ctx.setA(10);
    ctx.setB(4);
    ctx.setOperation(Operation::SUB);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 6);
}
TEST(CalculatorTest, MulTwoNumbers) {
    Context ctx;
    ctx.setA(6);
    ctx.setB(7);
    ctx.setOperation(Operation::MUL);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 42);
}
TEST(CalculatorTest, DivTwoNumbers) {
    Context ctx;
    ctx.setA(20);
    ctx.setB(4);
    ctx.setOperation(Operation::DIV);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 5);
}
TEST(CalculatorTest, PowOfNumber) {
    Context ctx;
    ctx.setA(2);
    ctx.setB(3);
    ctx.setOperation(Operation::POW);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 8);
}
TEST(CalculatorTest, FactOfNumber) {
    Context ctx;
    ctx.setA(5);
    ctx.setOperation(Operation::FACT);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 120);
}

// Factorial edge cases
TEST(CalculatorTest, FactOfZero) {
    Context ctx;
    ctx.setA(0);
    ctx.setOperation(Operation::FACT);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 1);
}
TEST(CalculatorTest, FactOfBigNum) {
    Context ctx;
    ctx.setA(15);
    ctx.setOperation(Operation::FACT);
    Calculator calc;
    EXPECT_THROW(calc.calculate(ctx), std::exception);
}

// Power edge cases
TEST(CalculatorTest, ZeroPowOfZero) {
    Context ctx;
    ctx.setA(0);
    ctx.setB(0);
    ctx.setOperation(Operation::POW);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 1);
}
TEST(CalculatorTest, AnyPowOfZero) {
    Context ctx;
    ctx.setA(2657);
    ctx.setB(0);
    ctx.setOperation(Operation::POW);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 1);
}
TEST(CalculatorTest, ZeroPowOfAny) {
    Context ctx;
    ctx.setA(0);
    ctx.setB(395);
    ctx.setOperation(Operation::POW);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 0);
}

// Negative numbers
TEST(CalculatorTest, AddNegativeNums) {
    Context ctx;
    ctx.setA(-5);
    ctx.setB(-3);
    ctx.setOperation(Operation::ADD);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), -8);
}
TEST(CalculatorTest, SubWithNegativeResult) {
    Context ctx;
    ctx.setA(3);
    ctx.setB(10);
    ctx.setOperation(Operation::SUB);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), -7);
}
TEST(CalculatorTest, MulNegativeNums) {
    Context ctx;
    ctx.setA(-5);
    ctx.setB(-3);
    ctx.setOperation(Operation::MUL);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 15);
}
TEST(CalculatorTest, DivNegativeNums) {
    Context ctx;
    ctx.setA(-20);
    ctx.setB(-4);
    ctx.setOperation(Operation::DIV);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 5);
}

// Operations with zero
TEST(CalculatorTest, MulByZero) {
    Context ctx;
    ctx.setA(5);
    ctx.setB(0);
    ctx.setOperation(Operation::MUL);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 0);
}
TEST(CalculatorTest, DivZero) {
    Context ctx;
    ctx.setA(0);
    ctx.setB(5);
    ctx.setOperation(Operation::DIV);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 0);
}

// Integer division
TEST(CalculatorTest, IntegerDivWithRemainder) {
    Context ctx;
    ctx.setA(7);
    ctx.setB(2);
    ctx.setOperation(Operation::DIV);
    Calculator calc;
    calc.calculate(ctx);
    EXPECT_EQ(ctx.getResult(), 3);
}

// Overflow 
TEST(CalculatorTest, PowOverflow) {
    Context ctx;
    ctx.setA(2);
    ctx.setB(31);
    ctx.setOperation(Operation::POW);
    Calculator calc;
    EXPECT_THROW(calc.calculate(ctx), std::exception);
}
