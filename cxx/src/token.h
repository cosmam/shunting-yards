#ifndef TOKEN_H
#define TOKEN_H

#include "value_type.h"

#include <functional>
#include <span>
#include <string>
#include <variant>

using CalcFunc = std::function<ValueType(std::span<ValueType>)>;

class Token
{
public:

    enum class TokenType {
        Comma,
        Function,
        Operator,
        Parenthesis,
        Value
    };

    Token(std::string_view text, TokenType t);

    Token(std::string_view text, TokenType t, CalcFunc func, int16_t precedence, int16_t arity, bool right_associative = true);

    auto text() const noexcept -> std::string_view;

    auto type() const noexcept -> TokenType;

    void setPrecedence(int16_t precedence);

    auto precedence() const noexcept -> int16_t;

    void setArity(int16_t arity);

    auto arity() const noexcept -> int16_t;

    void setRightAssociative(bool right_associative);

    auto rightAssociative() const noexcept -> bool;

    auto evaluate() const -> ValueType;

    auto evaluate(ValueType v1) const -> ValueType;

    auto evaluate(ValueType v1, ValueType v2) const -> ValueType;

    auto evaluate(std::span<ValueType> values) const -> ValueType;

private:

    std::string_view _text;
    TokenType _type;
    CalcFunc _func;
    int16_t _precedence = 0;
    int16_t _arity = 0;
    bool _right_associative = true;
};

#endif // TOKEN_H