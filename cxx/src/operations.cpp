#include "operations.h"

#include <cmath>
#include <concepts>
#include <stdexcept>

namespace {

    constexpr double Radians_Per_Degree = 6.283185307179586 / 360.0;

    template<typename T>
        requires std::same_as<T, int64_t> || std::same_as<T, double> || std::same_as<T, bool>
    auto getValue(const ValueType & value) -> T
    {
        if(std::holds_alternative<int64_t>(value)) {
            return static_cast<T>(std::get<int64_t>(value));
        } else if(std::holds_alternative<double>(value)) {
            return static_cast<T>(std::get<double>(value));
        } else if(std::holds_alternative<bool>(value)) {
            return static_cast<T>(std::get<bool>(value));
        }
        throw std::invalid_argument("Requested invalid type for variant");
    }

    auto hasDouble(std::span<ValueType> values) -> bool
    {
        return std::any_of(values.begin(), values.end(), [](auto && value) { return std::holds_alternative<double>(value); });
    }

    auto operator<=>(const ValueType & left, const ValueType& right) -> std::partial_ordering
    {
        if(std::holds_alternative<double>(left) || std::holds_alternative<double>(right)) {
            return (std::get<double>(left) <=> std::get<double>(right));
        } else {
            return (std::get<long>(left) <=> std::get<long>(right));
        }
    }
}

namespace Operations {

    auto aCos(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::acos(getValue<double>(values[0]));
    }

    auto aSin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::asin(getValue<double>(values[0]));
    }

    auto aTan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::atan(getValue<double>(values[0]));
    }

    auto abs(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::abs(getValue<double>(values[0]));
    }

    auto ln(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::log(getValue<double>(values[0]));
    }

    auto log(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::log10(getValue<double>(values[0]));
    }

    auto degree(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return getValue<double>(values[0]) * Radians_Per_Degree;
    }

    auto logicalNot(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto bitwiseNot(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto cos(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::cos(getValue<double>(values[0]));
    }

    auto sin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::sin(getValue<double>(values[0]));
    }

    auto tan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::tan(getValue<double>(values[0]));
    }

    auto round(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {
            return std::lround(getValue<double>(values[0]));
        } else if(std::holds_alternative<double>(values[1])) {
            
        } else if(std::holds_alternative<long>(values[1])) {

        }
        throw std::invalid_argument("Bool type not supported for operation");
    }

    auto floor(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {

        } else if(std::holds_alternative<double>(values[1])) {
            
        } else if(std::holds_alternative<long>(values[1])) {

        }
        throw std::invalid_argument("Bool type not supported for operation");
    }

    auto ceiling(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {

        } else if(std::holds_alternative<double>(values[1])) {
            
        } else if(std::holds_alternative<long>(values[1])) {

        }
        throw std::invalid_argument("Bool type not supported for operation");
    }

    auto plus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {
            return values[0];
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto minus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {
            return (hasDouble(values) ? ValueType(-1.0 * getValue<double>(values[0])) : ValueType(-1 * getValue<long>(values[0])));
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto equals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        return values[0] == values[1];
    }

    auto notEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        return values[0] != values[1];
    }

    auto lessThanEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        return values[0] <= values[1];
    }

    auto greaterThanEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        return values[0] >= values[1];
    }

    auto approximatelyEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {

        } else {

        }
        
    }

    auto multiply(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto divide(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto logicalAnd(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto logicalOr(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto bitshiftLeft(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto bitshiftRight(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto min(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto max(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto power(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {

        } else {

        }
    }

    auto modulo(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto remainder(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto bitwiseAnd(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto bitwiseOr(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto lessThan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        return values[0] < values[1];
    }

    auto greaterThan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        return values[0] > values[1];
    }
}