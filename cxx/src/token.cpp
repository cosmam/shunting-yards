#include "token.h"

#include <charconv>
#include <stdexcept>

namespace {
    template <class T, class... Args>
    auto convert(const char* first, const char* last, Args... args) -> T {
        T value;
        std::from_chars_result res = std::from_chars(first, last, value, args... );

        // These two exceptions reflect the behavior of std::stoi.
        if (res.ec == std::errc::invalid_argument) {
            throw std::invalid_argument{"invalid_argument"};
        } else if (res.ec == std::errc::result_out_of_range) {
            throw std::out_of_range{"out_of_range"};
        }

        return value;
    }
}


Token::Token(std::string_view text, TokenType t)
  : Token(text, t, CalcFunc(), 0, 0)
{
}

Token::Token(std::string_view text, TokenType t, CalcFunc func, int16_t precedence, int16_t arity, bool right_associative)
  : _text(text),
    _type(t),
    _func(func),
    _precedence(precedence),
    _arity(arity),
    _right_associative(right_associative)
{
    if(text.size() == 0) {
        throw std::invalid_argument("Token length must not be 0");
    }
}

auto Token::text() const noexcept -> std::string_view
{
    return _text;
}

auto Token::type() const noexcept -> TokenType
{
    return _type;
}

void Token::setPrecedence(int16_t precedence)
{
    _precedence = precedence;
}

auto Token::precedence() const noexcept -> int16_t
{
    return _precedence;
}

void Token::setArity(int16_t arity)
{
    _arity = arity;
}

auto Token::arity() const noexcept -> int16_t
{
    return _arity;
}

void Token::setRightAssociative(bool right_associative)
{
    _right_associative = right_associative;
}

auto Token::rightAssociative() const noexcept -> bool
{
    return _right_associative;
}

auto Token::evaluate() const -> ValueType
{
    if(_text == "true") {
        return true;
    } else if(_text == "false") {
        return false;
    } else if(_text.contains('.') || _text.contains('e')) {
        return convert<double>(_text.cbegin(), _text.cend());
    }

    return convert<int64_t>(_text.cbegin(), _text.cend());
}

auto Token::evaluate(ValueLookupFunc lookup_func) -> ValueType
{
    return lookup_func(_text);
}

auto Token::evaluate(ValueType v1) const -> ValueType
{
    return evaluate({v1});
}

auto Token::evaluate(ValueType v1, ValueType v2) const -> ValueType
{
    std::array values{v1, v2};
    return evaluate(values);
}

auto Token::evaluate(std::span<ValueType> values) const -> ValueType
{
    return _func(values);
}