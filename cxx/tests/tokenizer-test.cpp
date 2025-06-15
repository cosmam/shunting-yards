#include "../src/tokenizer.h"
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <span>

namespace {
    
    struct TokenizerTestData
    {
        TokenizerTestData() = default;
        TokenizerTestData(std::string s, const std::vector<std::string> & t) : str(s), tokens(t) {}

        std::string str;
        std::vector<std::string> tokens;
    };

    auto toString(std::span<Tokenizer::Token> tokens) -> std::vector<std::string>
    {
        std::vector<std::string> strs;
        for(auto && t : tokens) {
            strs.push_back(std::string(t.str));
        }
        return strs;
    }

    auto split(const std::string& s, const std::string& delimiter) -> std::vector<std::string>
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }


    auto readBasicData() -> std::vector<TokenizerTestData>
    {
        std::vector<TokenizerTestData> data;

        std::ifstream file("../../test_data/single_values.dat");
        std::string str; 
        while (std::getline(file, str))
        {
            auto pieces = split(str, ";");
            auto tokens = split(pieces.at(1), ",");

            data.push_back(TokenizerTestData(pieces.front(), tokens));
        }

        return data;
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

TEST(TokenizerTest, TestStallCase)
{
    std::string raw = "round(90)";
    std::vector<std::string> expected{"round", "(", "90", ")"};

    auto input = Tokenizer::preprocess(raw);
    auto tokens = Tokenizer::tokenize(input);

    EXPECT_EQ(toString(tokens), expected); 
}

TEST(TokenizerTest, TestBasicData)
{
    auto full_data = readBasicData();
    for(auto && data : full_data) {
        auto input = Tokenizer::preprocess(data.str);
        auto tokens = Tokenizer::tokenize(input);

        EXPECT_EQ(toString(tokens), data.tokens);        
    }
}

// class BasicTokenizerSuite : public ::testing::TestWithParam<TokenizerTestData> {};

// INSTANTIATE_TEST_SUITE_P(BasicTokenizerTest,
//                          BasicTokenizerSuite,
//                          testing::ValuesIn(readBasicData()));

// TEST_P(BasicTokenizerSuite, TestBasicTokenize)
// {
//     auto data = GetParam();

//     auto input = Tokenizer::preprocess(data.str);
//     auto tokens = Tokenizer::tokenize(input);

//     EXPECT_EQ(toString(tokens), data.tokens);
// };