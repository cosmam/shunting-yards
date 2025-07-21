#include "../src/operations.h"
#include <gtest/gtest.h>

#include <cmath>
#include <numbers>
#include <tuple>
#include <vector>

namespace {
    
    constexpr double pi = std::numbers::pi;

    const std::vector<ValueType> All_Value_Types{ValueType(-11.2), ValueType(-1.2), ValueType(0.0), ValueType(2.1), ValueType(20.1), 
        ValueType(-11L), ValueType(-3L), ValueType(0L), ValueType(4L), ValueType(32L), ValueType(true), ValueType(false)};

    auto convert(std::partial_ordering ordering) -> std::string
    {
        if(ordering == std::partial_ordering::less) {
            return "less";
        } else if(ordering == std::partial_ordering::equivalent) {
            return "equivalent";
        } else if(ordering == std::partial_ordering::greater) {
            return "greater";
        } else {
            return "unordered";
        }
    }
}

void PrintTo(const ValueType& value, std::ostream* os) {
    if(value.holdsAlternative<double>()) {
        *os << std::to_string(value.get<double>());
    } else if(value.holdsAlternative<int64_t>()) {
        *os << std::to_string(value.get<int64_t>());
    } else {
        *os << (value.get<bool>() ? "true" : "false");
    }
}

TEST(OperationsTest, testACosInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::aCos(values), std::invalid_argument);
}

TEST(OperationsTest, testACosInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::aCos(values), std::invalid_argument);
}

TEST(OperationsTest, testASinInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::aSin(values), std::invalid_argument);
}

TEST(OperationsTest, testASinInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::aSin(values), std::invalid_argument);
}

TEST(OperationsTest, testATanInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::aTan(values), std::invalid_argument);
}

TEST(OperationsTest, testATanInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::aTan(values), std::invalid_argument);
}

class InvTrigOperationsSuite : public ::testing::TestWithParam<ValueType> {};

INSTANTIATE_TEST_SUITE_P(InvTrigOperationsTest,
                         InvTrigOperationsSuite,
                         testing::Values(ValueType(0.0), ValueType(0L), ValueType(0.25), ValueType(.1312341), 
                                         ValueType(1.0), ValueType(1L), ValueType(true), ValueType(false)));

TEST_P(InvTrigOperationsSuite, testACos)
{
    auto value = GetParam();
    double input = value.get<double>();
    double expected = std::acos(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::aCos(tokens);
    EXPECT_TRUE(actual.holdsAlternative<double>());
    EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
};

TEST_P(InvTrigOperationsSuite, testASin)
{
    auto value = GetParam();
    double input = value.get<double>();
    double expected = std::asin(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::aSin(tokens);
    EXPECT_TRUE(actual.holdsAlternative<double>());
    EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
};

TEST_P(InvTrigOperationsSuite, testATan)
{
    auto value = GetParam();
    double input = value.get<double>();
    double expected = std::atan(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::aTan(tokens);
    EXPECT_TRUE(actual.holdsAlternative<double>());
    EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
};

TEST(OperationsTest, testCosInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::cos(values), std::invalid_argument);
}

TEST(OperationsTest, testCosInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::cos(values), std::invalid_argument);
}

TEST(OperationsTest, testSinInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::sin(values), std::invalid_argument);
}

TEST(OperationsTest, testSinInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::sin(values), std::invalid_argument);
}

TEST(OperationsTest, testTanInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::tan(values), std::invalid_argument);
}

TEST(OperationsTest, testTanInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::tan(values), std::invalid_argument);
}

class TrigOperationsSuite : public ::testing::TestWithParam<ValueType> {};

INSTANTIATE_TEST_SUITE_P(TrigOperationsTest,
                         TrigOperationsSuite,
                         testing::Values(ValueType(-2.0 * pi), ValueType(-1.0 * pi), ValueType(0.0), ValueType(pi), ValueType(2.0 * pi), 
                                         ValueType(0L), ValueType(2L), ValueType(-1L), ValueType(12L), ValueType(true), ValueType(false)));

TEST_P(TrigOperationsSuite, testCos)
{
    auto value = GetParam();
    double input = value.get<double>();
    double expected = std::cos(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::cos(tokens);
    EXPECT_TRUE(actual.holdsAlternative<double>());
    EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
};

TEST_P(TrigOperationsSuite, testSin)
{
    auto value = GetParam();
    double input = value.get<double>();
    double expected = std::sin(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::sin(tokens);
    EXPECT_TRUE(actual.holdsAlternative<double>());
    EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
};

TEST_P(TrigOperationsSuite, testTan)
{
    auto value = GetParam();
    double input = value.get<double>();
    double expected = std::tan(input);

    std::vector<ValueType> tokens{input};

    auto actual = Operations::tan(tokens);
    EXPECT_TRUE(actual.holdsAlternative<double>());
    EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
};

TEST(OperationsTest, testAbsInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::abs(values), std::invalid_argument);
}

TEST(OperationsTest, testAbsInvalidLog)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::abs(values), std::invalid_argument);
}

TEST(OperationsTest, testEqualsInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::equals(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::equals(values), std::invalid_argument);
}

TEST(OperationsTest, testEqualsInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::equals(values), std::invalid_argument);
}

TEST(OperationsTest, testNotEqualsInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::notEquals(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::notEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testNotEqualsInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::notEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testLessThanInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::lessThan(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::lessThan(values), std::invalid_argument);
}

TEST(OperationsTest, testLessThanInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::lessThan(values), std::invalid_argument);
}

TEST(OperationsTest, testLessThanEqualsInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::lessThanEquals(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::lessThanEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testLessThanEqualsInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::lessThanEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testGreaterThanInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::greaterThan(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::greaterThan(values), std::invalid_argument);
}

TEST(OperationsTest, testGreaterThanInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::greaterThan(values), std::invalid_argument);
}

TEST(OperationsTest, testGreaterThanEqualsInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::greaterThanEquals(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::greaterThanEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testGreaterThanEqualsInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::greaterThanEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testPlusInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::plus(values), std::invalid_argument);
}

TEST(OperationsTest, testPlusInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::plus(values), std::invalid_argument);
}

TEST(OperationsTest, testMinsInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::minus(values), std::invalid_argument);
}

TEST(OperationsTest, testMinsInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::minus(values), std::invalid_argument);
}

TEST(OperationsTest, testMultipliesInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::multiply(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::multiply(values), std::invalid_argument);
}

TEST(OperationsTest, testMultipliesInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::multiply(values), std::invalid_argument);
}

TEST(OperationsTest, testDividesInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::divide(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::divide(values), std::invalid_argument);
}

TEST(OperationsTest, testDividesInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::divide(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseAndInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::bitwiseAnd(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::bitwiseAnd(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseAndInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::bitwiseAnd(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseOrInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::bitwiseOr(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::bitwiseOr(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseOrInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::bitwiseOr(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseXorInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::bitwiseXor(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::bitwiseXor(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseXorInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::bitwiseXor(values), std::invalid_argument);
}

TEST(OperationsTest, testMinInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::min(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::min(values), std::invalid_argument);
}

TEST(OperationsTest, testMinInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::min(values), std::invalid_argument);
}

TEST(OperationsTest, testMaxInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::max(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::max(values), std::invalid_argument);
}

TEST(OperationsTest, testMaxInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::max(values), std::invalid_argument);
}

TEST(OperationsTest, testLogicalAndInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::logicalAnd(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::logicalAnd(values), std::invalid_argument);
}

TEST(OperationsTest, testLogicalAndInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::logicalAnd(values), std::invalid_argument);
}

TEST(OperationsTest, testLogicalOrInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::logicalOr(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::logicalOr(values), std::invalid_argument);
}

TEST(OperationsTest, testLogicalOrInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::logicalOr(values), std::invalid_argument);
}

TEST(OperationsTest, testModuloInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::modulo(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::modulo(values), std::invalid_argument);
}

TEST(OperationsTest, testModuloInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::modulo(values), std::invalid_argument);
}

TEST(OperationsTest, testRemainderInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::remainder(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::remainder(values), std::invalid_argument);
}

TEST(OperationsTest, testRemainderInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::remainder(values), std::invalid_argument);
}

TEST(OperationsTest, testBitshiftLeftInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::bitshiftLeft(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::bitshiftLeft(values), std::invalid_argument);
}

TEST(OperationsTest, testBitshiftLeftInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::bitshiftLeft(values), std::invalid_argument);
}

TEST(OperationsTest, testBitshiftRightInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::bitshiftRight(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::bitshiftRight(values), std::invalid_argument);
}

TEST(OperationsTest, testBitshiftRightInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::bitshiftRight(values), std::invalid_argument);
}

TEST(OperationsTest, testPowInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::power(values), std::invalid_argument);

    values.push_back(ValueType(0L));
    EXPECT_THROW(Operations::power(values), std::invalid_argument);
}

TEST(OperationsTest, tesPowInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::power(values), std::invalid_argument);
}

class ComparisonOperationsSuite : public ::testing::TestWithParam<std::tuple<ValueType, ValueType>> {};

INSTANTIATE_TEST_SUITE_P(ComparisonOperationsTest,
                         ComparisonOperationsSuite,
                         testing::Combine(testing::ValuesIn(All_Value_Types),
                                          testing::ValuesIn(All_Value_Types)));;

TEST_P(ComparisonOperationsSuite, testEquals)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::equals(tokens);
    bool expected = false;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left == right);
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left == right);
    }
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual.get<bool>(), expected);
};

TEST_P(ComparisonOperationsSuite, testNotEquals)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::notEquals(tokens);
    bool expected = false;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left != right);
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left != right);
    }
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual.get<bool>(), expected);
};

TEST_P(ComparisonOperationsSuite, testLessThan)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::lessThan(tokens);
    bool expected = false;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left < right);
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left < right);
    }
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual.get<bool>(), expected);
};

TEST_P(ComparisonOperationsSuite, testLessThanEquals)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::lessThanEquals(tokens);
    bool expected = false;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left <= right);
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left <= right);
    }
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual.get<bool>(), expected);
};

TEST_P(ComparisonOperationsSuite, testGreaterThan)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::greaterThan(tokens);
    bool expected = false;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left > right);
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left > right);
    }
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual.get<bool>(), expected);
};

TEST_P(ComparisonOperationsSuite, testGreaterThanEquals)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::greaterThanEquals(tokens);
    bool expected = false;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left >= right);
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left >= right);
    }
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual.get<bool>(), expected);
};

TEST_P(ComparisonOperationsSuite, testBinaryPlus)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::plus(tokens);
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left + right);
        EXPECT_TRUE(actual.holdsAlternative<double>());
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left + right);
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
    }
    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testBinaryMinus)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::minus(tokens);
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left - right);
        EXPECT_TRUE(actual.holdsAlternative<double>());
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left - right);
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
    }
    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testMultiply)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::multiply(tokens);
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = (left * right);
        EXPECT_TRUE(actual.holdsAlternative<double>());
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = (left * right);
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
    }
    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testDivision)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    bool error_expected = false;
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();

        if(right == 0.0) {
            EXPECT_THROW(Operations::divide(tokens), std::runtime_error);
        } else {
            auto actual = Operations::divide(tokens);
            expected = (left / right);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();

        if(right == 0) {
            EXPECT_THROW(Operations::divide(tokens), std::runtime_error);
        } else {
            auto actual = Operations::divide(tokens);
            expected = (left / right);
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, expected);
        }
    }  
};    
    
TEST_P(ComparisonOperationsSuite, testBitwiseAnd)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles are not valid
    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseAnd(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseAnd(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() & tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};
    
TEST_P(ComparisonOperationsSuite, testBitwiseOr)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles are not valid
    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseOr(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseOr(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() | tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};
    
TEST_P(ComparisonOperationsSuite, testBitwiseXor)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles are not valid
    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseXor(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseXor(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() ^ tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(ComparisonOperationsSuite, testMin)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::min(tokens);
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = std::min(left, right);
        EXPECT_TRUE(actual.holdsAlternative<double>());
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = std::min(left, right);
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
    }
    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testMax)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::max(tokens);
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        expected = std::max(left, right);
        EXPECT_TRUE(actual.holdsAlternative<double>());
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        expected = std::max(left, right);
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
    }
    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testLogicalAnd)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::logicalAnd(tokens);
    ValueType expected;

    bool left = tokens.at(0).get<bool>();
    bool right = tokens.at(1).get<bool>();
    expected = left && right;
    EXPECT_TRUE(actual.holdsAlternative<bool>());    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testLogicalOr)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    auto actual = Operations::logicalOr(tokens);
    ValueType expected;

    bool left = tokens.at(0).get<bool>();
    bool right = tokens.at(1).get<bool>();
    expected = left || right;
    EXPECT_TRUE(actual.holdsAlternative<bool>());    
    EXPECT_EQ(actual, expected);
};

TEST_P(ComparisonOperationsSuite, testModulo)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    bool error_expected = false;
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();

        if(right == 0.0) {
            EXPECT_THROW(Operations::modulo(tokens), std::runtime_error);
        } else {
            auto actual = Operations::modulo(tokens);
            expected = std::fmod(left, right);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();

        if(right == 0) {
            EXPECT_THROW(Operations::modulo(tokens), std::runtime_error);
        } else {
            auto actual = Operations::modulo(tokens);
            expected = (left % right);
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, expected);
        }
    }  
}; 

TEST_P(ComparisonOperationsSuite, testRemainder)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    bool error_expected = false;
    ValueType expected;

    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();

        if(right == 0.0) {
            EXPECT_THROW(Operations::remainder(tokens), std::runtime_error);
        } else {
            auto actual = Operations::remainder(tokens);
            expected = std::remainder(left, right);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();

        if(right == 0) {
            EXPECT_THROW(Operations::remainder(tokens), std::runtime_error);
        } else {
            auto actual = Operations::remainder(tokens);
            expected = std::remainder(left, right);
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, expected);
        }
    }  
}; 

TEST_P(ComparisonOperationsSuite, testBitshiftLeft)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles are not valid
    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitshiftLeft(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitshiftLeft(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() << tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(ComparisonOperationsSuite, testBitshiftRight)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles are not valid
    if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitshiftRight(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitshiftRight(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() >> tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(ComparisonOperationsSuite, testPower)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(1).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        double right = tokens.at(1).get<double>();
        if(left == 0.0 && right <= 0.0) {
            EXPECT_THROW(Operations::power(tokens), std::runtime_error);
        } else if(left < 0.0) {
            EXPECT_THROW(Operations::power(tokens), std::runtime_error);
        } else {
            auto actual = Operations::power(tokens);
            ValueType expected = std::pow(left, right);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    } else if(tokens.at(0).holdsAlternative<double>()) {
        double left = tokens.at(0).get<double>();
        int64_t right = tokens.at(1).get<int64_t>();
        if(left == 0.0 && right <= 0) {
            EXPECT_THROW(Operations::power(tokens), std::runtime_error);
        } else {
            auto actual = Operations::power(tokens);
            ValueType expected = std::pow(left, right);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    } else {
        int64_t left = tokens.at(0).get<int64_t>();
        int64_t right = tokens.at(1).get<int64_t>();
        if(left == 0 && right <= 0) {
            EXPECT_THROW(Operations::power(tokens), std::runtime_error);
        } else {
            auto actual = Operations::power(tokens);
            ValueType expected = std::pow(left, right);
            if(right < 0 || expected.get<double>() > (double)std::numeric_limits<int64_t>::max()) {
                EXPECT_TRUE(actual.holdsAlternative<double>());
            } else {
                EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            }
            EXPECT_EQ(actual, expected);
        }
    }
};