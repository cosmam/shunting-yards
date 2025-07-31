#include "../src/equation_evaluator.h"
#include <gtest/gtest.h>

#include "../src/token.h"

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

    auto toString(const std::vector<Token> & tokens) -> std::vector<std::string>
    {
        std::vector<std::string> strs;
        for(auto && t : tokens) {
            strs.push_back(std::string(t.text()));
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
            auto pieces = split(str, ":");
            auto tokens = split(pieces.at(1), ";");

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

TEST_P(StringTransformSuite, testTransforms)
{
    auto params = GetParam();
    auto before = std::get<0>(params);
    auto expected = std::get<1>(params);

    EXPECT_EQ(EquationEvaluator::preprocess(before), expected);
};

// TEST(TokenizerTest, testBasicTokenize)
// {
//     std::string input = "sin(2.10*3)^2";
//     std::vector<std::string> expected{"sin", "(", "2.10", "*", "3", ")", "^", "2"};
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(toString(tokens), expected);
// }

// TEST(TokenizerTest, testPlusArity1)
// {
//     std::string input = "+2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 2);
//     EXPECT_EQ(tokens.front().text(), "+");
//     EXPECT_EQ(tokens.front().arity(), 1);
// }

// TEST(TokenizerTest, testPlusArity2)
// {
//     std::string input = "2+2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens.at(1).text(), "+");
//     EXPECT_EQ(tokens.at(1).arity(), 2);
// }

// TEST(TokenizerTest, testPlusArity3)
// {
//     std::string input = ")+2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens.at(1).text(), "+");
//     EXPECT_EQ(tokens.at(1).arity(), 2);
// }

// TEST(TokenizerTest, testPlusArity4)
// {
//     std::string input = "(+2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens.at(1).text(), "+");
//     EXPECT_EQ(tokens.at(1).arity(), 1);
// }

// TEST(TokenizerTest, testPlusArity5)
// {
//     std::string input = "2++2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 4);
//     EXPECT_EQ(tokens.at(1).text(), "+");
//     EXPECT_EQ(tokens.at(1).arity(), 2);
//     EXPECT_EQ(tokens.at(2).text(), "+");
//     EXPECT_EQ(tokens.at(2).arity(), 1);
// }

// TEST(TokenizerTest, testMinusArity1)
// {
//     std::string input = "-2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 2);
//     EXPECT_EQ(tokens.front().text(), "-");
//     EXPECT_EQ(tokens.front().arity(), 1);
// }

// TEST(TokenizerTest, testMinusArity2)
// {
//     std::string input = "2-2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens.at(1).text(), "-");
//     EXPECT_EQ(tokens.at(1).arity(), 2);
// }

// TEST(TokenizerTest, testMinusArity3)
// {
//     std::string input = ")-2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens.at(1).text(), "-");
//     EXPECT_EQ(tokens.at(1).arity(), 2);
// }

// TEST(TokenizerTest, testMinusArity4)
// {
//     std::string input = "(-2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens.at(1).text(), "-");
//     EXPECT_EQ(tokens.at(1).arity(), 1);
// }

// TEST(TokenizerTest, testMinusArity5)
// {
//     std::string input = "2--2";
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(tokens.size(), 4);
//     EXPECT_EQ(tokens.at(1).text(), "-");
//     EXPECT_EQ(tokens.at(1).arity(), 2);
//     EXPECT_EQ(tokens.at(2).text(), "-");
//     EXPECT_EQ(tokens.at(2).arity(), 1);
// }

// TEST(TokenizerTest, testStallCase)
// {
//     std::string raw = "round(90)";
//     std::vector<std::string> expected{"round", "(", "90", ")"};

//     auto input = EquationEvaluator::preprocess(raw);
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(toString(tokens), expected); 
// }

// TEST(TokenizerTest, testComma)
// {
//     std::string raw = "round(90,10)";
//     std::vector<std::string> expected{"round", "(", "90", ",", "10", ")"};

//     auto input = EquationEvaluator::preprocess(raw);
//     auto tokens = EquationEvaluator::tokenize(input);

//     EXPECT_EQ(toString(tokens), expected); 
// }

// // TEST(TokenizerTest, testBasicData)
// // {
// //     auto full_data = readBasicData();
// //     for(auto && data : full_data) {
// //         try {
// //             auto input = Tokenizer::preprocess(data.str);
// //             auto tokens = EquationEvaluator::tokenize(input);

// //             EXPECT_EQ(toString(tokens), data.tokens);        
// //         } catch(const std::exception & e) {
// //             std::cout << data.str << std::endl;
// //         }
// //     }
// // }

// // symbol, precedence, right-associative
// class UnaryOperatorData : public ::testing::TestWithParam<std::tuple<std::string, int16_t, bool>> {};

// INSTANTIATE_TEST_SUITE_P(UnaryOperatorSuite,
//                          UnaryOperatorData,
//                          testing::Values(std::tuple{"+", 3, true}, 
//                                          std::tuple{"-", 3, true}, 
//                                          std::tuple{"~", 3, true}, 
//                                          std::tuple{"!", 3, true}, 
//                                          std::tuple{"°", 3, false}));

// TEST_P(UnaryOperatorData, testUnaryOperatorData)
// {
//     auto params = GetParam();
//     auto symbol = std::get<0>(params);
//     auto precedence = std::get<1>(params);
//     auto right_associative = std::get<2>(params);

//     std::string str = (right_associative ? symbol : "") + std::string("2") + (right_associative ? "" : symbol);

//     auto tokens = EquationEvaluator::tokenize(str);

//     auto token = tokens.at(right_associative ? 0 : 1);

//     EXPECT_EQ(token.arity(), 1);
//     EXPECT_EQ(token.precedence(), precedence);
//     EXPECT_EQ(token.rightAssociative(), right_associative);
// };

// // symbol, precedence
// class BinaryOperatorData : public ::testing::TestWithParam<std::tuple<std::string, int16_t>> {};

// INSTANTIATE_TEST_SUITE_P(BinaryOperatorSuite,
//                          BinaryOperatorData,
//                          testing::Values(std::tuple{"==", 16},
//                                          std::tuple{"!=", 16},
//                                          std::tuple{"/=", 16},
//                                          std::tuple{"<=", 9},
//                                          std::tuple{">=", 9},
//                                          std::tuple{"~=", 16},
//                                          std::tuple{"+", 6},
//                                          std::tuple{"-", 6},
//                                          std::tuple{"*", 5},
//                                          std::tuple{"/", 5},
//                                          std::tuple{"^", 4},
//                                          std::tuple{"%", 5},
//                                          std::tuple{"&&", 14},
//                                          std::tuple{"||", 15},
//                                          std::tuple{"<<", 7},
//                                          std::tuple{">>", 7},
//                                          std::tuple{"&", 11},
//                                          std::tuple{"|", 13},
//                                          std::tuple{"<", 9},
//                                          std::tuple{">", 9}));

// TEST_P(BinaryOperatorData, testBinaryOperatorData)
// {
//     auto params = GetParam();
//     auto symbol = std::get<0>(params);
//     auto precedence = std::get<1>(params);

//     std::string str = std::string("2") + symbol + std::string("2");

//     auto tokens = EquationEvaluator::tokenize(str);

//     auto token = tokens.at(1);

//     EXPECT_EQ(token.arity(), 2);
//     EXPECT_EQ(token.precedence(), precedence);
// };