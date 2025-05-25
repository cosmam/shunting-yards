#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

namespace Tokenizer {

    enum class TokenType {
        Function,
        Operator,
        Parenthesis,
        Value
    };

    struct Token {
        Token() = default;
        Token(std::string_view s, TokenType t) : str(s), type(t) {}

        std::string_view str;
        TokenType type;
    };

    void initialize();
}

#endif // TOKENIZER_H