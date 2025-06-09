#include "../src/tokenizer.h"
#include <gtest/gtest.h>

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