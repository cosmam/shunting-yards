#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "token.h"
#include "value_type.h"

#include <span>

namespace Operations {

    auto aCos(std::span<ValueType> values) -> ValueType;

    auto aSin(std::span<ValueType> values) -> ValueType;

    auto aTan(std::span<ValueType> values) -> ValueType;

    auto abs(std::span<ValueType> values) -> ValueType;

    auto ln(std::span<ValueType> values) -> ValueType;

    auto log(std::span<ValueType> values) -> ValueType;

    auto exp(std::span<ValueType> values) -> ValueType;

    auto degree(std::span<ValueType> values) -> ValueType;

    auto logicalNot(std::span<ValueType> values) -> ValueType;

    auto bitwiseNot(std::span<ValueType> values) -> ValueType;

    auto cos(std::span<ValueType> values) -> ValueType;

    auto sin(std::span<ValueType> values) -> ValueType;

    auto tan(std::span<ValueType> values) -> ValueType;

    auto round(std::span<ValueType> values) -> ValueType;

    auto floor(std::span<ValueType> values) -> ValueType;

    auto ceiling(std::span<ValueType> values) -> ValueType;

    auto plus(std::span<ValueType> values) -> ValueType;

    auto minus(std::span<ValueType> values) -> ValueType;

    auto equals(std::span<ValueType> values) -> ValueType;

    auto notEquals(std::span<ValueType> values) -> ValueType;

    auto lessThanEquals(std::span<ValueType> values) -> ValueType;

    auto greaterThanEquals(std::span<ValueType> values) -> ValueType;

    auto approximatelyEquals(std::span<ValueType> values) -> ValueType;

    auto multiply(std::span<ValueType> values) -> ValueType;

    auto divide(std::span<ValueType> values) -> ValueType;

    auto bitwiseAnd(std::span<ValueType> values) -> ValueType;

    auto bitwiseOr(std::span<ValueType> values) -> ValueType;

    auto bitwiseXor(std::span<ValueType> values) -> ValueType;

    auto bitshiftLeft(std::span<ValueType> values) -> ValueType;

    auto bitshiftRight(std::span<ValueType> values) -> ValueType;

    auto min(std::span<ValueType> values) -> ValueType;

    auto max(std::span<ValueType> values) -> ValueType;

    auto power(std::span<ValueType> values) -> ValueType;

    auto modulo(std::span<ValueType> values) -> ValueType;

    auto remainder(std::span<ValueType> values) -> ValueType;

    auto logicalAnd(std::span<ValueType> values) -> ValueType;

    auto logicalOr(std::span<ValueType> values) -> ValueType;

    auto lessThan(std::span<ValueType> values) -> ValueType;

    auto greaterThan(std::span<ValueType> values) -> ValueType;
}

#endif // EQUATION_EVALUATOR_H