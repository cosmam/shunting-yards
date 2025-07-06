#include "../src/operations.h"
#include <gtest/gtest.h>

#include <cmath>
#include <numbers>

namespace {
    
    constexpr double pi = std::numbers::pi;

    template<typename T>
        requires std::same_as<T, int64_t> || std::same_as<T, double> || std::same_as<T, bool>
    auto getValue(const ValueType & value) -> T
    {
        if(std::holds_alternative<int64_t>(value)) {
            return static_cast<T>(std::get<int64_t>(value));
        } else if(std::holds_alternative<double>(value)) {
            return static_cast<T>(std::get<double>(value));
        } 
        return static_cast<T>(std::get<bool>(value));
    }
}

TEST(OperationsTest, testACosInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::aCos(values), std::invalid_argument);
}

TEST(OperationsTest, testACosInvalidLong)
{
    std::vector<ValueType> values{ValueType(0), ValueType(0)};
    EXPECT_THROW(Operations::aCos(values), std::invalid_argument);
}

TEST(OperationsTest, testASinInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::aSin(values), std::invalid_argument);
}

TEST(OperationsTest, testASinInvalidLong)
{
    std::vector<ValueType> values{ValueType(0), ValueType(0)};
    EXPECT_THROW(Operations::aSin(values), std::invalid_argument);
}

TEST(OperationsTest, testATanInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::aTan(values), std::invalid_argument);
}

TEST(OperationsTest, testATanInvalidLong)
{
    std::vector<ValueType> values{ValueType(0), ValueType(0)};
    EXPECT_THROW(Operations::aTan(values), std::invalid_argument);
}

class InvTrigOperationsSuite : public ::testing::TestWithParam<ValueType> {};

INSTANTIATE_TEST_SUITE_P(InvTrigOperationsTest,
                         InvTrigOperationsSuite,
                         testing::Values(ValueType(0.0), ValueType(0), ValueType(0.25), ValueType(.1312341), 
                                         ValueType(1.0), ValueType(1), ValueType(true), ValueType(false)));

TEST_P(InvTrigOperationsSuite, testACos)
{
    auto value = GetParam();
    double input = getValue<double>(value);
    double expected = std::acos(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::aCos(tokens);
    EXPECT_TRUE(std::holds_alternative<double>(actual));
    EXPECT_DOUBLE_EQ(getValue<double>(actual), expected);
};

TEST_P(InvTrigOperationsSuite, testASin)
{
    auto value = GetParam();
    double input = getValue<double>(value);
    double expected = std::asin(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::aSin(tokens);
    EXPECT_TRUE(std::holds_alternative<double>(actual));
    EXPECT_DOUBLE_EQ(getValue<double>(actual), expected);
};

TEST_P(InvTrigOperationsSuite, testATan)
{
    auto value = GetParam();
    double input = getValue<double>(value);
    double expected = std::atan(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::aTan(tokens);
    EXPECT_TRUE(std::holds_alternative<double>(actual));
    EXPECT_DOUBLE_EQ(getValue<double>(actual), expected);
};

TEST(OperationsTest, testCosInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::cos(values), std::invalid_argument);
}

TEST(OperationsTest, testCosInvalidLong)
{
    std::vector<ValueType> values{ValueType(0), ValueType(0)};
    EXPECT_THROW(Operations::cos(values), std::invalid_argument);
}

TEST(OperationsTest, testSinInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::sin(values), std::invalid_argument);
}

TEST(OperationsTest, testSinInvalidLong)
{
    std::vector<ValueType> values{ValueType(0), ValueType(0)};
    EXPECT_THROW(Operations::sin(values), std::invalid_argument);
}

TEST(OperationsTest, testTanInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::tan(values), std::invalid_argument);
}

TEST(OperationsTest, testTanInvalidLong)
{
    std::vector<ValueType> values{ValueType(0), ValueType(0)};
    EXPECT_THROW(Operations::tan(values), std::invalid_argument);
}

class TrigOperationsSuite : public ::testing::TestWithParam<ValueType> {};

INSTANTIATE_TEST_SUITE_P(TrigOperationsTest,
                         TrigOperationsSuite,
                         testing::Values(ValueType(-2.0 * pi), ValueType(-1.0 * pi), ValueType(0.0), ValueType(pi), ValueType(2.0 * pi), 
                                         ValueType(0), ValueType(2), ValueType(-1), ValueType(12), ValueType(true), ValueType(false)));

TEST_P(TrigOperationsSuite, testCos)
{
    auto value = GetParam();
    double input = getValue<double>(value);
    double expected = std::cos(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::cos(tokens);
    EXPECT_TRUE(std::holds_alternative<double>(actual));
    EXPECT_DOUBLE_EQ(getValue<double>(actual), expected);
};

TEST_P(TrigOperationsSuite, testSin)
{
    auto value = GetParam();
    double input = getValue<double>(value);
    double expected = std::sin(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::sin(tokens);
    EXPECT_TRUE(std::holds_alternative<double>(actual));
    EXPECT_DOUBLE_EQ(getValue<double>(actual), expected);
};

TEST_P(TrigOperationsSuite, testTan)
{
    auto value = GetParam();
    double input = getValue<double>(value);
    double expected = std::tan(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::tan(tokens);
    EXPECT_TRUE(std::holds_alternative<double>(actual));
    EXPECT_DOUBLE_EQ(getValue<double>(actual), expected);
};