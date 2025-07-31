#include "../src/operations.h"
#include <gtest/gtest.h>

#include <cmath>
#include <numbers>
#include <tuple>
#include <vector>

namespace {
    
    constexpr double tau = 2.0 * std::numbers::pi;
    constexpr double Radians_Per_Degree = tau / 360.0;

    const std::vector<ValueType> All_Value_Types{ValueType(-11.2), ValueType(-1.2), ValueType(-1.0), ValueType(0.0), ValueType(1.0), ValueType(2.1), 
        ValueType(20.1), ValueType(-11L), ValueType(-3L), ValueType(0L), ValueType(4L), ValueType(32L), ValueType(true), ValueType(false)};

    const std::vector<ValueType> Rounding_Bases{ValueType(0.0), ValueType(-1.23e-4), ValueType(2.87e3), ValueType(-2.12e2),
        ValueType(3.87e3), ValueType(-4e-12), ValueType(5.12e13), ValueType(-1.2e29), ValueType(2.3e32), ValueType(0L), ValueType(1L),
        ValueType(-2L), ValueType(123L), ValueType(-12091L), ValueType(1231290L), ValueType(-120198012L), ValueType(true), ValueType(false)};

    const std::vector<ValueType> Rounding_Scale{ValueType(0.0), ValueType(0L), ValueType(2.0), ValueType(2L), ValueType(3.5), ValueType(12.0),
        ValueType(-1.2), ValueType(123.123123), ValueType(69L), ValueType(true), ValueType(false)};

    const std::vector<int64_t> Double_Ulp_Distance{-5L, -4L, -3L, -1L, 0L, 1L, 3L, 4L, 5L};

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

    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::aCos(tokens), std::invalid_argument);
    } else {
        double expected = std::acos(value.get<double>());
        auto actual = Operations::aCos(tokens);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
    }
};

TEST_P(InvTrigOperationsSuite, testASin)
{
    auto value = GetParam();

    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::aSin(tokens), std::invalid_argument);
    } else {
        double expected = std::asin(value.get<double>());
        auto actual = Operations::aSin(tokens);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
    }
};

TEST_P(InvTrigOperationsSuite, testATan)
{
    auto value = GetParam();

    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::aTan(tokens), std::invalid_argument);
    } else {
        double expected = std::atan(value.get<double>());
        auto actual = Operations::aTan(tokens);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
    }
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
                         testing::Values(ValueType(-1.0 * tau), ValueType(-0.5 * tau), ValueType(0.0), ValueType(0.5 * tau), ValueType(tau), 
                                         ValueType(0L), ValueType(2L), ValueType(-1L), ValueType(12L), ValueType(true), ValueType(false)));

TEST_P(TrigOperationsSuite, testCos)
{
    auto value = GetParam();

    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::cos(tokens), std::invalid_argument);
    } else {
        double expected = std::cos(value.get<double>());
        auto actual = Operations::cos(tokens);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
    }
};

TEST_P(TrigOperationsSuite, testSin)
{
    auto value = GetParam();

    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::sin(tokens), std::invalid_argument);
    } else {
        double expected = std::sin(value.get<double>());
        auto actual = Operations::sin(tokens);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
    }
};

TEST_P(TrigOperationsSuite, testTan)
{
    auto value = GetParam();

    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::tan(tokens), std::invalid_argument);
    } else {
        double expected = std::tan(value.get<double>());
        auto actual = Operations::tan(tokens);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_DOUBLE_EQ(actual.get<double>(), expected);
    }
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

TEST(OperationsTest, testMinusInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::minus(values), std::invalid_argument);
}

TEST(OperationsTest, testMinusInvalidLong)
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

TEST(OperationsTest, testMaxInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::max(values), std::invalid_argument);

    values.push_back(ValueType(0L));
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

TEST(OperationsTest, testPowInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::power(values), std::invalid_argument);
}

TEST(OperationsTest, testLogInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::log(values), std::invalid_argument);
}

TEST(OperationsTest, testLogInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::log(values), std::invalid_argument);
}

TEST(OperationsTest, testRoundInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::round(values), std::invalid_argument);
}

TEST(OperationsTest, testRoundInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::round(values), std::invalid_argument);
}

TEST(OperationsTest, testCeilingInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::ceiling(values), std::invalid_argument);
}

TEST(OperationsTest, testCeilingInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::ceiling(values), std::invalid_argument);
}

TEST(OperationsTest, testFloorInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::floor(values), std::invalid_argument);
}

TEST(OperationsTest, testFloorInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::floor(values), std::invalid_argument);
}

TEST(OperationsTest, testApproximatelyEqualsShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::approximatelyEquals(values), std::invalid_argument);
}

TEST(OperationsTest, testApproximatelyEqualsLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::approximatelyEquals(values), std::invalid_argument);
}

class TwoValuesSuite : public ::testing::TestWithParam<std::tuple<ValueType, ValueType>> {};

INSTANTIATE_TEST_SUITE_P(TwoValuesTest,
                         TwoValuesSuite,
                         testing::Combine(testing::ValuesIn(All_Value_Types),
                                          testing::ValuesIn(All_Value_Types)));;

TEST_P(TwoValuesSuite, testEquals)
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

TEST_P(TwoValuesSuite, testNotEquals)
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

TEST_P(TwoValuesSuite, testLessThan)
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

TEST_P(TwoValuesSuite, testLessThanEquals)
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

TEST_P(TwoValuesSuite, testGreaterThan)
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

TEST_P(TwoValuesSuite, testGreaterThanEquals)
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

TEST_P(TwoValuesSuite, testBinaryPlus)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::plus(tokens), std::invalid_argument);
    } else {
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
    }
};

TEST_P(TwoValuesSuite, testBinaryMinus)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::minus(tokens), std::invalid_argument);
    } else {
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
    }
};

TEST_P(TwoValuesSuite, testMultiply)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::multiply(tokens), std::invalid_argument);
    } else {
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
    }
};

TEST_P(TwoValuesSuite, testDivision)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    bool error_expected = false;
    ValueType expected;

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::divide(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
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
    
TEST_P(TwoValuesSuite, testBitwiseAnd)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles and bools are not valid
    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::bitwiseAnd(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseAnd(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseAnd(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() & tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};
    
TEST_P(TwoValuesSuite, testBitwiseOr)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles and bools are not valid
    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::bitwiseOr(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseOr(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseOr(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() | tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};
    
TEST_P(TwoValuesSuite, testBitwiseXor)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles and bools are not valid
    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::bitwiseXor(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseXor(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseXor(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() ^ tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(TwoValuesSuite, testMin)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    
    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::min(tokens), std::invalid_argument);
    } else {
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
    }
};

TEST_P(TwoValuesSuite, testMax)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::max(tokens), std::invalid_argument);
    } else {
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
    }
};

TEST_P(TwoValuesSuite, testLogicalAnd)
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

TEST_P(TwoValuesSuite, testLogicalOr)
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

TEST_P(TwoValuesSuite, testModulo)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    
    bool error_expected = false;
    ValueType expected;

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::modulo(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
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

TEST_P(TwoValuesSuite, testRemainder)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};
    bool error_expected = false;
    ValueType expected;

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::remainder(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
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

TEST_P(TwoValuesSuite, testBitshiftLeft)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles and bools are not valid
    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::bitshiftLeft(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitshiftLeft(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitshiftLeft(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() << tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(TwoValuesSuite, testBitshiftRight)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    // for binary operations, doubles and bools are not valid
    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::bitshiftRight(tokens), std::invalid_argument);
    } else if(tokens.at(0).holdsAlternative<double>() || tokens.at(1).holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitshiftRight(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitshiftRight(tokens);
        ValueType expected = tokens.at(0).get<int64_t>() >> tokens.at(1).get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(TwoValuesSuite, testPower)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::power(tokens), std::invalid_argument);
    } else if(tokens.at(1).holdsAlternative<double>()) {
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

TEST_P(TwoValuesSuite, testBinaryLog)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    auto v1 = tokens[0].get<double>();
    auto v2 = tokens[1].get<double>();

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::log(tokens), std::invalid_argument);
    } else if(v1 <= 0.0 || v2 <= 0.0) {
        EXPECT_THROW(Operations::log(tokens), std::runtime_error);
    } else {
        auto divisor = std::log(v2);
        if(divisor == 0.0) {
            EXPECT_THROW(Operations::log(tokens), std::runtime_error);
        } else {
            auto actual = Operations::log(tokens);
            ValueType expected = std::log(v1) / std::log(v2);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    }
};

TEST(OperationsTest, testLnInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::ln(values), std::invalid_argument);
}

TEST(OperationsTest, testLnInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::ln(values), std::invalid_argument);
}

TEST(OperationsTest, testExpInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::exp(values), std::invalid_argument);
}

TEST(OperationsTest, testExpInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::exp(values), std::invalid_argument);
}

TEST(OperationsTest, testDegreeInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::degree(values), std::invalid_argument);
}

TEST(OperationsTest, testDegreeInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::degree(values), std::invalid_argument);
}

TEST(OperationsTest, testLogicalNotInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::logicalNot(values), std::invalid_argument);
}

TEST(OperationsTest, testLogicalNotInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::logicalNot(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseNotInvalidShort)
{
    std::vector<ValueType> values(0);
    EXPECT_THROW(Operations::bitwiseNot(values), std::invalid_argument);
}

TEST(OperationsTest, testBitwiseNotInvalidLong)
{
    std::vector<ValueType> values{ValueType(0L), ValueType(0L)};
    EXPECT_THROW(Operations::bitwiseNot(values), std::invalid_argument);
}

class OneValueSuite : public ::testing::TestWithParam<ValueType> {};

INSTANTIATE_TEST_SUITE_P(OneValueTest,
                         OneValueSuite,
                         testing::ValuesIn(All_Value_Types));;

TEST_P(OneValueSuite, testUnaryPlus)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::plus(tokens), std::invalid_argument);
    } else {
        auto actual = Operations::plus(tokens);
        ValueType expected;

        if(value.holdsAlternative<double>()) {
            EXPECT_TRUE(actual.holdsAlternative<double>());
            expected = value;
        } else {
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            expected = value;
        }
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(OneValueSuite, testUnaryMinus)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
    
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::minus(tokens), std::invalid_argument);
    } else {
        auto actual = Operations::minus(tokens);
        ValueType expected;

        if(value.holdsAlternative<double>()) {
            EXPECT_TRUE(actual.holdsAlternative<double>());
            expected = -1.0 * value.get<double>();
        } else {
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            expected = -1 * value.get<int64_t>();
        }
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(OneValueSuite, testAbs)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
    
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::abs(tokens), std::invalid_argument);
    } else { 
        auto actual = Operations::abs(tokens);
        ValueType expected;

        if(value.holdsAlternative<double>()) {
            EXPECT_TRUE(actual.holdsAlternative<double>());
            expected = std::abs(value.get<double>());
        } else {
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            expected = std::abs(value.get<int64_t>());
        }
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(OneValueSuite, testLn)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
    
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::ln(tokens), std::invalid_argument);
    } else { 
        double exp = value.get<double>();

        if(exp <= 0.0) {
            EXPECT_THROW(Operations::ln(tokens), std::runtime_error);
        } else {
            auto actual = Operations::ln(tokens);
            ValueType expected = std::log(exp);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    }
};

TEST_P(OneValueSuite, testUnaryLog)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
    
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::log(tokens), std::invalid_argument);
    } else { 
        double exp = value.get<double>();

        if(exp <= 0.0) {
            EXPECT_THROW(Operations::log(tokens), std::runtime_error);
        } else {
            auto actual = Operations::log(tokens);
            ValueType expected = std::log10(exp);
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    }
};

TEST_P(OneValueSuite, testExp)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
    
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::exp(tokens), std::invalid_argument);
    } else { 
        double exp = value.get<double>();

        auto actual = Operations::exp(tokens);
        ValueType expected = std::exp(exp);
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(OneValueSuite, testDegrees)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
    
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::degree(tokens), std::invalid_argument);
    } else { 
        auto actual = Operations::degree(tokens);
        ValueType expected = value.get<double>() * Radians_Per_Degree;
        EXPECT_TRUE(actual.holdsAlternative<double>());
        EXPECT_EQ(actual, expected);
    }
};

TEST_P(OneValueSuite, testLogicalNot)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};

    auto actual = Operations::logicalNot(tokens);
    ValueType expected = !value.get<bool>();
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual, expected);
};

TEST_P(OneValueSuite, testBitwiseNot)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};
        
    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::bitwiseNot(tokens), std::invalid_argument);
    } else if(value.holdsAlternative<double>()) {
        EXPECT_THROW(Operations::bitwiseNot(tokens), std::runtime_error);
    } else {
        auto actual = Operations::bitwiseNot(tokens);
        ValueType expected = ~value.get<int64_t>();
        EXPECT_TRUE(actual.holdsAlternative<int64_t>());
        EXPECT_EQ(actual, expected);
    }
};

class RoundingOneValueSuite : public ::testing::TestWithParam<ValueType> {};

INSTANTIATE_TEST_SUITE_P(RoudningOneValuesTest,
                         RoundingOneValueSuite,
                         testing::ValuesIn(Rounding_Bases));

TEST_P(RoundingOneValueSuite, testSingleRound)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::round(tokens), std::invalid_argument);
    } else { 
        auto expected = std::round(value.get<double>());
        auto actual = Operations::round(tokens);

        if(expected < (double)std::numeric_limits<int64_t>::max()) {  
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, (int64_t)expected);
        } else {
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    }
};

TEST_P(RoundingOneValueSuite, testSingleFloor)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::floor(tokens), std::invalid_argument);
    } else { 
        auto expected = std::floor(value.get<double>());
        auto actual = Operations::floor(tokens);

        if(expected < (double)std::numeric_limits<int64_t>::max()) {  
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, (int64_t)expected);
        } else {
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    }
};

TEST_P(RoundingOneValueSuite, testSingleCeil)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value};

    if(value.holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::ceiling(tokens), std::invalid_argument);
    } else { 
        auto expected = std::ceil(value.get<double>());
        auto actual = Operations::ceiling(tokens);

        if(expected < (double)std::numeric_limits<int64_t>::max()) {  
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, (int64_t)expected);
        } else {
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        }
    }
};

TEST_P(RoundingOneValueSuite, testSelfApproximatelyEquals)
{
    auto value = GetParam();
    std::vector<ValueType> tokens{value, value};
    auto actual = Operations::approximatelyEquals(tokens);

    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_TRUE(actual.get<bool>());
};

class RoundingTwoValuesSuite : public ::testing::TestWithParam<std::tuple<ValueType, ValueType>> {};

INSTANTIATE_TEST_SUITE_P(RoudningTwoValuesTest,
                         RoundingTwoValuesSuite,
                         testing::Combine(testing::ValuesIn(Rounding_Bases),
                                          testing::ValuesIn(Rounding_Scale)));

TEST_P(RoundingTwoValuesSuite, testRound)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::round(tokens), std::invalid_argument);
    } else if(tokens.at(1).get<double>() <= 0.0) {
        EXPECT_THROW(Operations::round(tokens), std::runtime_error);
    } else {
        auto scale_factor = tokens.at(1).get<double>();
        auto expected = std::round(tokens.at(0).get<double>() / scale_factor) * scale_factor;
        auto actual = Operations::round(tokens);
        
        if(tokens.at(1).holdsAlternative<double>() || expected > (double)std::numeric_limits<int64_t>::max()) {  
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        } else {
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, (int64_t)expected);
        }
    }
};

TEST_P(RoundingTwoValuesSuite, testFloor)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::floor(tokens), std::invalid_argument);
    } else if(tokens.at(1).get<double>() <= 0.0) {
        EXPECT_THROW(Operations::floor(tokens), std::runtime_error);
    } else {
        auto scale_factor = tokens.at(1).get<double>();
        auto expected = std::floor(tokens.at(0).get<double>() / scale_factor) * scale_factor;
        auto actual = Operations::floor(tokens);
        
        if(tokens.at(1).holdsAlternative<double>() || expected > (double)std::numeric_limits<int64_t>::max()) {  
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        } else {
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, (int64_t)expected);
        }
    }
};

TEST_P(RoundingTwoValuesSuite, testCeiling)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    if(tokens.at(0).holdsAlternative<bool>() || tokens.at(1).holdsAlternative<bool>()) {
        EXPECT_THROW(Operations::ceiling(tokens), std::invalid_argument);
    } else if(tokens.at(1).get<double>() <= 0.0) {
        EXPECT_THROW(Operations::ceiling(tokens), std::runtime_error);
    } else {
        auto scale_factor = tokens.at(1).get<double>();
        auto expected = std::ceil(tokens.at(0).get<double>() / scale_factor) * scale_factor;
        auto actual = Operations::ceiling(tokens);
        
        if(tokens.at(1).holdsAlternative<double>() || expected > (double)std::numeric_limits<int64_t>::max()) {  
            EXPECT_TRUE(actual.holdsAlternative<double>());
            EXPECT_EQ(actual, expected);
        } else {
            EXPECT_TRUE(actual.holdsAlternative<int64_t>());
            EXPECT_EQ(actual, (int64_t)expected);
        }
    }
};

TEST_P(RoundingTwoValuesSuite, testApproximatelyEquals)
{
    auto values = GetParam();
    std::vector<ValueType> tokens{std::get<0>(values), std::get<1>(values)};

    ValueType expected(tokens.at(0).get<double>() == tokens.at(1).get<double>());
    
    auto actual = Operations::approximatelyEquals(tokens);
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual, expected);
};

TEST(OperationsTest, testApproximatelyEqualsNan)
{
    ValueType val1(1.0);
    ValueType val2(std::numeric_limits<double>::quiet_NaN());

    std::vector<ValueType> v1{val1, val2};
    std::vector<ValueType> v2{val2, val1};

    auto actual1 = Operations::approximatelyEquals(v1);
    auto actual2 = Operations::approximatelyEquals(v2);

    EXPECT_TRUE(actual1.holdsAlternative<bool>());
    EXPECT_TRUE(actual2.holdsAlternative<bool>());

    EXPECT_EQ(actual1.get<bool>(), false);
    EXPECT_EQ(actual2.get<bool>(), false);
}

class RoundingUlpSuite : public ::testing::TestWithParam<std::tuple<ValueType, int64_t>> {};

INSTANTIATE_TEST_SUITE_P(RoundingUlpTest,
                         RoundingUlpSuite,
                         testing::Combine(testing::ValuesIn(Rounding_Bases),
                                          testing::ValuesIn(Double_Ulp_Distance)));

TEST_P(RoundingUlpSuite, testApproximatelyEquals)
{
    auto values = GetParam();
    double val1 = std::get<0>(values).get<double>();
    auto int_val1 = (int64_t)std::bit_cast<uint64_t>(val1);
    double val2 = 0.0;

    if(val1 == 0.0 && std::get<1>(values) < 0) {
        int_val1 += std::abs(std::get<1>(values));
        val2 = std::bit_cast<double>(int_val1);
        val2 *= -1.0;
    } else {
        int_val1 += std::get<1>(values);
        val2 = std::bit_cast<double>(int_val1);
    }

    bool expected = std::abs(std::get<1>(values)) <= 4;

    std::vector<ValueType> tokens{std::get<0>(values), ValueType(val2)};
    
    auto actual = Operations::approximatelyEquals(tokens);
    EXPECT_TRUE(actual.holdsAlternative<bool>());
    EXPECT_EQ(actual, expected);
};                                          