#include "value_type.h"


ValueType::ValueType(double value)
  : _value(value)
{}

ValueType::ValueType(long value)
  : _value(value)
{}

ValueType::ValueType(bool value)
  : _value(value)
{}

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