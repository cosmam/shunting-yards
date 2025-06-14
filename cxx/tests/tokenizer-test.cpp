#include "../src/tokenizer.h"
#include <gtest/gtest.h>

#include <span>

namespace {
    auto toString(std::span<Tokenizer::Token> tokens) -> std::vector<std::string>
    {
        std::vector<std::string> strs;
        for(auto && t : tokens) {
            strs.push_back(std::string(t.str));
        }
        return strs;
    }
}

class StringTransformSuite : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};

INSTANTIATE_TEST_SUITE_P(PreprocessTest,
                         StringTransformSuite,
                         testing::Values(std::tuple{"test", "test"}, 
                                         std::tuple{"te st", "test"}, 
                                         std::tuple{"TeSt", "test"}, 
                                         std::tuple{" tE s t", "test"}));

TEST_P(StringTransformSuite, TestTransforms)
{
    auto params = GetParam();
    auto before = std::get<0>(params);
    auto expected = std::get<1>(params);

    EXPECT_EQ(Tokenizer::preprocess(before), expected);
};

TEST(TokenizerTest, TestBasicTokenize)
{
    std::string input = "sin(2.10*3)^2";
    std::vector<std::string> expected{"sin", "(", "2.10", "*", "3", ")", "^", "2"};
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(toString(tokens), expected);
}

TEST(TokenizerTest, TestPlusArity1)
{
    std::string input = "+2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens.front().str, "+");
    EXPECT_EQ(tokens.front().arity, 1);
}

TEST(TokenizerTest, TestPlusArity2)
{
    std::string input = "2+2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(1).str, "+");
    EXPECT_EQ(tokens.at(1).arity, 2);
}

TEST(TokenizerTest, TestPlusArity3)
{
    std::string input = ")+2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(1).str, "+");
    EXPECT_EQ(tokens.at(1).arity, 2);
}

TEST(TokenizerTest, TestPlusArity4)
{
    std::string input = "(+2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(1).str, "+");
    EXPECT_EQ(tokens.at(1).arity, 1);
}

TEST(TokenizerTest, TestPlusArity5)
{
    std::string input = "2++2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens.at(1).str, "+");
    EXPECT_EQ(tokens.at(1).arity, 2);
    EXPECT_EQ(tokens.at(2).str, "+");
    EXPECT_EQ(tokens.at(2).arity, 1);
}

TEST(TokenizerTest, TestMinusArity1)
{
    std::string input = "-2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens.front().str, "-");
    EXPECT_EQ(tokens.front().arity, 1);
}

TEST(TokenizerTest, TestMinusArity2)
{
    std::string input = "2-2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(1).str, "-");
    EXPECT_EQ(tokens.at(1).arity, 2);
}

TEST(TokenizerTest, TestMinusArity3)
{
    std::string input = ")-2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(1).str, "-");
    EXPECT_EQ(tokens.at(1).arity, 2);
}

TEST(TokenizerTest, TestMinusArity4)
{
    std::string input = "(-2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens.at(1).str, "-");
    EXPECT_EQ(tokens.at(1).arity, 1);
}

TEST(TokenizerTest, TestMinusArity5)
{
    std::string input = "2--2";
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens.at(1).str, "-");
    EXPECT_EQ(tokens.at(1).arity, 2);
    EXPECT_EQ(tokens.at(2).str, "-");
    EXPECT_EQ(tokens.at(2).arity, 1);
}