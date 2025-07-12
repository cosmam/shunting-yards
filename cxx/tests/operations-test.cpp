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