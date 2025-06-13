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