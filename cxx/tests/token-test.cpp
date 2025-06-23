#include "../src/token.h"
#include <gtest/gtest.h>

namespace {

    auto testCalcFunc(std::span<ValueType> values) -> ValueType
    {
        return 0;
    }
}

TEST(TokenTest, testText)
{
    std::string text = "test";
    Token token(text, Token::TokenType::Function);

    EXPECT_EQ(token.text(), text);
}

TEST(TokenTest, testInvalidText)
{
    EXPECT_THROW(Token("", Token::TokenType::Function), std::invalid_argument);
}

TEST(TokenTest, testType)
{
    auto type = Token::TokenType::Function;
    Token token("text", type);

    EXPECT_EQ(token.type(), type);
}

TEST(TokenTest, testTextFull)
{
    std::string text = "test";
    Token token(text, Token::TokenType::Function, &testCalcFunc, -1, -1);

    EXPECT_EQ(token.text(), text);
}

TEST(TokenTest, testInvalidTextFull)
{
    EXPECT_THROW(Token("", Token::TokenType::Function, &testCalcFunc, -1, -1), std::invalid_argument);
}

TEST(TokenTest, testTypeFull)
{
    auto type = Token::TokenType::Function;
    Token token("text", type, &testCalcFunc, -1, -1);

    EXPECT_EQ(token.type(), type);
}

TEST(TokenTest, testPrecedence)
{
    int16_t value = 2;
    Token token("text", Token::TokenType::Function, &testCalcFunc, value, -1);

    EXPECT_EQ(token.precedence(), value);
}

TEST(TokenTest, testArity)
{
    int16_t value = 2;
    Token token("text", Token::TokenType::Function, &testCalcFunc, -1, value);

    EXPECT_EQ(token.arity(), value);
}

TEST(TokenTest, testEvaluateBool1)
{
    Token token("true", Token::TokenType::Value);

    auto value = token.evaluate();

    EXPECT_EQ(std::get<bool>(value), true);
}

TEST(TokenTest, testEvaluateBool2)
{
    Token token("false", Token::TokenType::Value);

    auto value = token.evaluate();

    EXPECT_EQ(std::get<bool>(value), false);
}

class DoubleEvaluateSuite : public ::testing::TestWithParam<std::tuple<std::string, double>> {};

INSTANTIATE_TEST_SUITE_P(DoubleEvaluateTest,
                         DoubleEvaluateSuite,
                         testing::Values(std::tuple{"0.1", 0.1}, 
                                         std::tuple{".2", 0.2}, 
                                         std::tuple{"1e2", 100.0}, 
                                         std::tuple{"1.2e2", 120.0}, 
                                         std::tuple{"1.1e+2", 110.0}, 
                                         std::tuple{"1.2e-2", 0.012}, 
                                         std::tuple{"12e-2", 0.12}));

TEST_P(DoubleEvaluateSuite, testValidDoubleEvaluate)
{
    auto params = GetParam();
    auto text = std::get<0>(params);
    auto expected = std::get<1>(params);

    Token token(text, Token::TokenType::Value);

    auto value = token.evaluate();

    EXPECT_DOUBLE_EQ(std::get<double>(value), expected);
};

TEST(TokenTest, testIntegerEvaluation)
{
    Token token("12", Token::TokenType::Value);

    auto value = token.evaluate();

    EXPECT_EQ(std::get<int64_t>(value), 12);    
}

TEST(TokenTest, testIntegerEvaluationLeadingZero)
{
    Token token("0123", Token::TokenType::Value);

    auto value = token.evaluate();

    EXPECT_EQ(std::get<int64_t>(value), 123);    
}
