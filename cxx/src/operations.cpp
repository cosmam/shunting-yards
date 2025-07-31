#include "operations.h"

#include <cmath>
#include <concepts>
#include <stdexcept>

#include <iostream>

namespace {

    constexpr int64_t Max_Double_Ulp_Distance = 4;
    constexpr double Radians_Per_Degree = 2.0 * std::numbers::pi / 360.0;

    auto hasDouble(std::span<ValueType> values) -> bool
    {
        return std::any_of(values.begin(), values.end(), [](auto && value) { return value.template holdsAlternative<double>(); });
    }

    auto hasBool(std::span<ValueType> values) -> bool
    {
        return std::any_of(values.begin(), values.end(), [](auto && value) { return value.template holdsAlternative<bool>(); });
    }

    auto intIfPossible(double value) -> ValueType
    {
        if(value > static_cast<double>(std::numeric_limits<int64_t>::max())) {
            return static_cast<double>(value);
        }
        return static_cast<int64_t>(value);
    }

    auto isZero(const ValueType & value) -> bool
    {
        if(value.holdsAlternative<double>()) {
            return value.get<double>() == 0.0;
        }
        return value.get<int64_t>() == 0;
    }
    
    auto isPositive(const ValueType & value) -> bool
    {
        if(value.holdsAlternative<double>()) {
            return value.get<double>() > 0.0;
        }
        return value.get<int64_t>() > 0;
    }

    // Function to calculate ULPs distance between two doubles
    auto ulpsDistance(double a, double b) -> int64_t 
    {
        // Handle special cases:
        // If either is NaN, the distance is effectively infinite (or max_int64)
        if (std::isnan(a) || std::isnan(b)) {
            return std::numeric_limits<int64_t>::max();
        }

        // If both are equal, distance is 0 (handles +0.0 and -0.0)
        if (a == b) {
            return 0;
        }

        // Convert to positive and add their ULP distances from zero.
        uint64_t int_a = std::bit_cast<uint64_t>(a);
        uint64_t int_b = std::bit_cast<uint64_t>(b);

        if(int_a == 0L || int_b == 0L) {
            auto distance = std::fabs(a - b);
            return std::bit_cast<uint64_t>(distance);
        } else if (std::signbit(a) != std::signbit(b)) {
            // If signs are different and neither is zero, then they are far apart.
            // This handles cases like -1.0 and +1.0

            // For negative numbers, the bit pattern comparison is reversed.
            // So, if a is negative, its "integer" value is larger than positive numbers with smaller magnitude.
            // To get a consistent "distance from zero", we need to adjust for negative numbers' bit representation.
            if (std::signbit(a)) {
                int_a = (uint64_t)1 << (std::numeric_limits<uint64_t>::digits - 1) - int_a;
            }
            if (std::signbit(b)) {
                int_b = (uint64_t)1 << (std::numeric_limits<uint64_t>::digits - 1) - int_b;
            }
            return std::abs(std::abs(static_cast<int64_t>(int_a) - static_cast<int64_t>(int_b)));
        }

        return std::abs(std::abs(static_cast<int64_t>(int_a) - static_cast<int64_t>(int_b)));
    }
}

namespace Operations {

    auto aCos(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return std::acos(values[0].get<double>());
    }

    auto aSin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return std::asin(values[0].get<double>());
    }

    auto aTan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return std::atan(values[0].get<double>());
    }

    auto abs(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        if(hasDouble(values)) {
            return std::abs(values[0].get<double>());    
        }

        return std::abs(values[0].get<int64_t>());
    }

    auto ln(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(!isPositive(values[0])) {
            throw std::runtime_error("Invalid parameter to ln function");
        }

        return std::log(values[0].get<double>());
    }

    auto log(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(!isPositive(values[0])) {
            throw std::runtime_error("Invalid parameter to log function");
        }

        if(values.size() == 2) {
            auto divisor = ln(values.subspan(1,1)).get<double>();
            if(divisor == 0.0) {
                throw std::runtime_error("Division by zero in binary log computation");
            }
            return ln(values.subspan(0,1)).get<double>() / divisor;
        }

        return std::log10(values[0].get<double>());
    }

    auto exp(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }

        return std::exp(values[0].get<double>());
    }

    auto degree(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return values[0].get<double>() * Radians_Per_Degree;
    }

    auto logicalNot(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        }

        return !values[0].get<bool>();
    }

    auto bitwiseNot(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            throw std::runtime_error("Bitwise operations not valid on doubles");
        }

        return ~values[0].get<int64_t>();
    }

    auto cos(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return std::cos(values[0].get<double>());
    }

    auto sin(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return std::sin(values[0].get<double>());
    }

    auto tan(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 1) {
            throw std::invalid_argument("Invalid value count; expected one");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        }
        
        return std::tan(values[0].get<double>());
    }

    auto round(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(values.size() == 1) {
            return intIfPossible(std::round(values[0].get<double>()));
        }
        
        if(!isPositive(values[1])) {
            throw std::runtime_error("Cannot round based on non-positive number");
        }

        auto scale_factor = values[1].get<double>();    // even if it's an int64_t, we can get it as a double for the math
        auto temp = values[0].get<double>() / scale_factor;
        temp = std::round(temp) * scale_factor;
        return (values[1].holdsAlternative<double>() ? ValueType(static_cast<double>(temp)) : intIfPossible(temp));
    }

    auto floor(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(values.size() == 1) {
            return intIfPossible(std::floor(values[0].get<double>()));
        }

        if(!isPositive(values[1])) {
            throw std::runtime_error("Cannot round based on non-positive number");
        }

        auto scale_factor = values[1].get<double>();    // even if it's an int64_t, we can get it as a double for the math
        auto temp = values[0].get<double>() / scale_factor;
        temp = std::floor(temp) * scale_factor;
        return (values[1].holdsAlternative<double>() ? ValueType(static_cast<double>(temp)) : intIfPossible(temp));
    }

    auto ceiling(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(values.size() == 1) {
            return intIfPossible(std::ceil(values[0].get<double>()));
        }

        if(!isPositive(values[1])) {
            throw std::runtime_error("Cannot round based on non-positive number");
        }

        auto scale_factor = values[1].get<double>();    // even if it's an int64_t, we can get it as a double for the math
        auto temp = values[0].get<double>() / scale_factor;
        temp = std::ceil(temp) * scale_factor;
        return (values[1].holdsAlternative<double>() ? ValueType(static_cast<double>(temp)) : intIfPossible(temp));
    }

    auto plus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(values.size() == 1) {
            return (hasDouble(values) ? ValueType(values[0].get<double>()) : ValueType(values[0].get<int64_t>()));
        } else if(hasDouble(values)) {
            return values[0].get<double>() + values[1].get<double>();
        }

        return values[0].get<int64_t>() + values[1].get<int64_t>();
    }

    auto minus(std::span<ValueType> values) -> ValueType
    {
        if(values.size() == 0 || values.size() > 2) {
            throw std::invalid_argument("Invalid value count; expected one or two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(values.size() == 1) {
            return (hasDouble(values) ? ValueType(-1.0 * values[0].get<double>()) : ValueType(-1 * values[0].get<int64_t>()));
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
            return std::abs(ulpsDistance(values[0].get<double>(), values[1].get<double>())) <= Max_Double_Ulp_Distance;
        }

        return equals(values);
    }

    auto multiply(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            return values[0].get<double>() * values[1].get<double>();
        }

        return values[0].get<int64_t>() * values[1].get<int64_t>();
    }

    auto divide(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(isZero(values[1])) {
            throw std::runtime_error("Divide by zero");
        } else if(hasDouble(values)) {
            return values[0].get<double>() / values[1].get<double>();
        }

        return values[0].get<int64_t>() / values[1].get<int64_t>();
    }

    auto bitwiseAnd(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            throw std::runtime_error("Bitwise operations not valid on doubles");
        }

        return values[0].get<int64_t>() & values[1].get<int64_t>();
    }

    auto bitwiseOr(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            throw std::runtime_error("Bitwise operations not valid on doubles");
        }

        return values[0].get<int64_t>() | values[1].get<int64_t>();
    }

    auto bitwiseXor(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            throw std::runtime_error("Bitwise operations not valid on doubles");
        }

        return values[0].get<int64_t>() ^ values[1].get<int64_t>();
    }

    auto bitshiftLeft(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            throw std::runtime_error("Bitwise operations not valid on doubles");
        }

        return values[0].get<int64_t>() << values[1].get<int64_t>();
    }

    auto bitshiftRight(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            throw std::runtime_error("Bitwise operations not valid on doubles");
        }

        return values[0].get<int64_t>() >> values[1].get<int64_t>();
    }

    auto min(std::span<ValueType> values) -> ValueType
    {
        if(values.size() < 2) {
            throw std::invalid_argument("Invalid value count; expected at least two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            auto value = values[0].get<double>();
            for(size_t i=1 ; i < values.size() ; ++i) {
                value = std::min(value, values[i].get<double>());
            }
            return value;
        }

        auto value = values[0].get<int64_t>();
        for(size_t i=1 ; i < values.size() ; ++i) {
            value = std::min(value, values[i].get<int64_t>());
        }
        return value;
    }

    auto max(std::span<ValueType> values) -> ValueType
    {
        if(values.size() < 2) {
            throw std::invalid_argument("Invalid value count; expected at least two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(hasDouble(values)) {
            auto value = values[0].get<double>();
            for(size_t i=1 ; i < values.size() ; ++i) {
                value = std::max(value, values[i].get<double>());
            }
            return value;
        }

        auto value = values[0].get<int64_t>();
        for(size_t i=1 ; i < values.size() ; ++i) {
            value = std::max(value, values[i].get<int64_t>());
        }
        return value;
    }

    auto power(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(isZero(values[0]) && !isPositive(values[1])) {
            throw std::runtime_error("Can't raise zero to a power less than or equal to zero");
        } else if(values[1].holdsAlternative<double>()) {
            auto base = values[0].get<double>();
            if(base < 0.0) {
                throw std::runtime_error("Can't raise negative floating point value to non-integer value");
            }
            return std::pow(base, values[1].get<double>());
        } else if(values[0].holdsAlternative<double>()) {
            return static_cast<double>(std::pow(values[0].get<double>(), values[1].get<int64_t>()));
        }

        auto exp = values[1].get<int64_t>();
        return (exp < 0 ? std::pow(values[0].get<int64_t>(), exp) : intIfPossible(std::pow(values[0].get<int64_t>(), exp)));
    }

    auto modulo(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(isZero(values[1])) {
            throw std::runtime_error("Divide by zero");
        } else if(hasDouble(values)) {
            return std::fmod(values[0].get<double>(), values[1].get<double>());
        }

        return static_cast<int64_t>((values[0].get<int64_t>() % values[1].get<int64_t>()));
    }

    auto remainder(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        } else if(hasBool(values)) {
            throw std::invalid_argument("Invalid operation on boolean type");
        } else if(isZero(values[1])) {
            throw std::runtime_error("Divide by zero");
        } else if(hasDouble(values)) {
            return std::remainder(values[0].get<double>(), values[1].get<double>());
        }

        return static_cast<int64_t>(std::remainder(values[0].get<int64_t>(), values[1].get<int64_t>()));
    }

    auto logicalAnd(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }

        return values[0].get<bool>() && values[1].get<bool>();
    }

    auto logicalOr(std::span<ValueType> values) -> ValueType
    {
        if(values.size() != 2) {
            throw std::invalid_argument("Invalid value count; expected two");
        }

        return values[0].get<bool>() || values[1].get<bool>();
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

