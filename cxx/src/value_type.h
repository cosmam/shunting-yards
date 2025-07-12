#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H

#include <compare>
#include <concepts>
#include <cstdint>
#include <stdexcept>
#include <variant>

class ValueType
{
public:

    ValueType() = default;

    ValueType(double value);

    ValueType(long value);

    ValueType(bool value);

    // ValueType(ValueType& other) = default;
    // ValueType& operator=(ValueType& other) = default;

    template<typename T>
        requires std::same_as<T, int64_t> || std::same_as<T, double> || std::same_as<T, bool>
    auto holdsAlternative() const -> bool
    {
        return std::holds_alternative<T>(_value);
    }

    template<typename T>
        requires std::same_as<T, int64_t> || std::same_as<T, double> || std::same_as<T, bool>
    auto get() const -> T
    {
        if(std::holds_alternative<int64_t>(_value)) {
            return static_cast<T>(std::get<int64_t>(_value));
        } else if(std::holds_alternative<double>(_value)) {
            return static_cast<T>(std::get<double>(_value));
        } else if(std::holds_alternative<bool>(_value)) {
            return static_cast<T>(std::get<bool>(_value));
        }
        throw std::invalid_argument("Requested invalid type for variant");
    }

    auto operator<=>(const ValueType& other) const -> std::partial_ordering;

    auto operator==(const ValueType &other) const -> bool;

private:

    std::variant<int64_t, double, bool> _value;
};

#endif // VALUE_TYPE_H