#include "operations.h"

#include <concepts>
#include <stdexcept>

namespace {

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
}

namespace Operations {

    auto aCos(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto aSin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto aTan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto abs(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto ln(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto log(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto degree(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
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
        
    }

    auto sin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto tan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
    }

    auto round(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        }
        
    }

    auto floor(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        }
        
    }

    auto ceiling(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        }
        
    }

    auto plus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        }
        
    }

    auto minus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        }
        
    }

    auto equals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto notEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto lessThanEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto greaterThanEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto approximatelyEquals(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto multiply(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto divide(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
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
        }
        
    }

    auto max(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }

    auto power(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
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
        
    }

    auto greaterThan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }
        
    }
}