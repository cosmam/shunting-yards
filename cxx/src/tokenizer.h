#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

namespace Tokenizer {

    enum class TokenType {
        Comma,
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
        int16_t arity = 0;
        int16_t precedence = 0;
        bool right_associative = true;
    };

    auto preprocess(std::string_view str) -> std::string;

    auto tokenize(std::string_view str) -> std::vector<Token>;
}

#endif // TOKENIZER_H