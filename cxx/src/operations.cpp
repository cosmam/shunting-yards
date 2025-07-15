#include "operations.h"

#include <cmath>
#include <concepts>
#include <stdexcept>

#include <iostream>

namespace {

    constexpr double Radians_Per_Degree = 6.283185307179586 / 360.0;

    auto hasDouble(std::span<ValueType> values) -> bool
    {
        return std::any_of(values.begin(), values.end(), [](auto && value) { return value.template holdsAlternative<double>(); });
    }
}

namespace Operations {

    auto aCos(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::acos(values[0].get<double>());
    }

    auto aSin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::asin(values[0].get<double>());
    }

    auto aTan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::atan(values[0].get<double>());
    }

    auto abs(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        if(hasDouble(values)) {
            return std::abs(values[0].get<double>());    
        }
        return std::abs(values[0].get<long>());
    }

    auto ln(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::log(values[0].get<double>());
    }

    auto log(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::log10(values[0].get<double>());
    }

    auto degree(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return values[0].get<double>() * Radians_Per_Degree;
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
        
        return std::cos(values[0].get<double>());
    }

    auto sin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::sin(values[0].get<double>());
    }

    auto tan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }
        
        return std::tan(values[0].get<double>());
    }

    auto round(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {
            return std::lround(values[0].get<double>());
        } else if(values[1].holdsAlternative<double>()) {
            
        } else if(values[1].holdsAlternative<long>()) {

        }
        throw std::invalid_argument("Bool type not supported for operation");
    }

    auto floor(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {

        } else if(values[1].holdsAlternative<double>()) {
            
        } else if(values[1].holdsAlternative<long>()) {

        }
        throw std::invalid_argument("Bool type not supported for operation");
    }

    auto ceiling(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {

        } else if(values[1].holdsAlternative<double>()) {
            
        } else if(values[1].holdsAlternative<long>()) {

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
            return values[0].get<double>() + values[1].get<double>();
        }
        return values[0].get<int64_t>() + values[1].get<int64_t>();
    }

    auto minus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(values.size() == 1) {
            return (hasDouble(values) ? ValueType(-1.0 * values[0].get<double>()) : ValueType(-1 * values[0].get<long>()));
        } else if(hasDouble(values)) {
            return values[0].get<double>() - values[1].get<double>();
        }
        return values[0].get<int64_t>() - values[1].get<int64_t>();
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
            return values[0].get<double>() * values[1].get<double>();
        }
        return values[0].get<int64_t>() * values[1].get<int64_t>();
    }

    auto divide(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {
            return values[0].get<double>() / values[1].get<double>();
        }
        return values[0].get<int64_t>() / values[1].get<int64_t>();
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
            return std::min(values[0].get<double>(), values[1].get<double>());
        }
        return std::min(values[0].get<int64_t>(), values[1].get<int64_t>());
    }

    auto max(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasDouble(values)) {
            return std::max(values[0].get<double>(), values[1].get<double>());
        }
        return std::max(values[0].get<int64_t>(), values[1].get<int64_t>());
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

