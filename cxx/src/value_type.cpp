#include "value_type.h"


ValueType::ValueType(double value)
  : _value(value)
{}

ValueType::ValueType(long value)
  : _value(value)
{}

ValueType::ValueType(bool value, bool is_break)
  : _value(value),
    _is_break(is_break)
{}

auto ValueType::isBreak() const noexcept -> bool
{
  return _is_break;
}

auto ValueType::operator<=>(const ValueType& other) const -> std::partial_ordering
{
    if(std::holds_alternative<double>(_value) || std::holds_alternative<double>(other._value)) {
        return (get<double>() <=> other.get<double>());
    } else {
        return (get<long>() <=> other.get<long>());
    }
}

auto ValueType::operator==(const ValueType &other) const -> bool
{
    if(std::holds_alternative<double>(_value) || std::holds_alternative<double>(other._value)) {
        return (get<double>() == other.get<double>());
    } else {
        return (get<long>() == other.get<long>());
    }    
}