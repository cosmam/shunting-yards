#include "tokenizer.h"

#include <algorithm>
#include <map>

namespace {

    const std::vector<std::string> Token_Names{"(", ")", "0", "1", "2", "3", "4", "5", "6", "7", "8", 
                                               "9", ".", "e", "+", "-", "*", "/", "^", "%", "&&", 
                                               "||", "<<", ">>", "°", "!", "~", "min", "max", "pow", "mod", 
                                               "rem", "round", "acos", "asin", "atan", "abs", "ln", "log", "floor", "ceiling", 
                                               "==", "!=", "/=", "<=", ">=", "~=", "&", "|", "cos", "sin", 
                                               "tan", "ceil", "<", ">"};

    auto createMap() -> std::map<std::string_view, Tokenizer::Token>
    {
        std::map<std::string_view, Tokenizer::Token> tokens;

        tokens[Token_Names.at(0)] = Tokenizer::Token(Token_Names.at(0), Tokenizer::TokenType::Parenthesis);
        tokens[Token_Names.at(1)] = Tokenizer::Token(Token_Names.at(1), Tokenizer::TokenType::Parenthesis);
        tokens[Token_Names.at(2)] = Tokenizer::Token(Token_Names.at(2), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(3)] = Tokenizer::Token(Token_Names.at(3), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(4)] = Tokenizer::Token(Token_Names.at(4), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(5)] = Tokenizer::Token(Token_Names.at(5), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(6)] = Tokenizer::Token(Token_Names.at(6), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(7)] = Tokenizer::Token(Token_Names.at(7), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(8)] = Tokenizer::Token(Token_Names.at(8), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(9)] = Tokenizer::Token(Token_Names.at(9), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(10)] = Tokenizer::Token(Token_Names.at(10), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(11)] = Tokenizer::Token(Token_Names.at(11), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(12)] = Tokenizer::Token(Token_Names.at(12), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(13)] = Tokenizer::Token(Token_Names.at(13), Tokenizer::TokenType::Value);
        tokens[Token_Names.at(14)] = Tokenizer::Token(Token_Names.at(14), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(15)] = Tokenizer::Token(Token_Names.at(15), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(16)] = Tokenizer::Token(Token_Names.at(16), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(17)] = Tokenizer::Token(Token_Names.at(17), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(18)] = Tokenizer::Token(Token_Names.at(18), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(19)] = Tokenizer::Token(Token_Names.at(19), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(20)] = Tokenizer::Token(Token_Names.at(20), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(21)] = Tokenizer::Token(Token_Names.at(21), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(22)] = Tokenizer::Token(Token_Names.at(22), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(23)] = Tokenizer::Token(Token_Names.at(23), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(24)] = Tokenizer::Token(Token_Names.at(24), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(25)] = Tokenizer::Token(Token_Names.at(25), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(26)] = Tokenizer::Token(Token_Names.at(26), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(27)] = Tokenizer::Token(Token_Names.at(27), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(28)] = Tokenizer::Token(Token_Names.at(28), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(29)] = Tokenizer::Token(Token_Names.at(29), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(30)] = Tokenizer::Token(Token_Names.at(30), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(31)] = Tokenizer::Token(Token_Names.at(31), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(32)] = Tokenizer::Token(Token_Names.at(32), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(33)] = Tokenizer::Token(Token_Names.at(33), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(34)] = Tokenizer::Token(Token_Names.at(34), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(35)] = Tokenizer::Token(Token_Names.at(35), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(36)] = Tokenizer::Token(Token_Names.at(36), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(37)] = Tokenizer::Token(Token_Names.at(37), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(38)] = Tokenizer::Token(Token_Names.at(38), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(39)] = Tokenizer::Token(Token_Names.at(39), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(40)] = Tokenizer::Token(Token_Names.at(40), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(41)] = Tokenizer::Token(Token_Names.at(41), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(42)] = Tokenizer::Token(Token_Names.at(42), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(43)] = Tokenizer::Token(Token_Names.at(43), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(44)] = Tokenizer::Token(Token_Names.at(44), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(45)] = Tokenizer::Token(Token_Names.at(45), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(46)] = Tokenizer::Token(Token_Names.at(46), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(47)] = Tokenizer::Token(Token_Names.at(47), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(48)] = Tokenizer::Token(Token_Names.at(48), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(49)] = Tokenizer::Token(Token_Names.at(49), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(50)] = Tokenizer::Token(Token_Names.at(50), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(51)] = Tokenizer::Token(Token_Names.at(51), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(52)] = Tokenizer::Token(Token_Names.at(52), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(53)] = Tokenizer::Token(Token_Names.at(53), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(54)] = Tokenizer::Token(Token_Names.at(54), Tokenizer::TokenType::Operator);

        return tokens;
    } 

    const std::map<std::string_view, Tokenizer::Token> Tokens = createMap();
}

namespace Tokenizer {

    auto preprocess(std::string_view str) -> std::string
    {
        std::string s(str);
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
        s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
        return s;
    }

    auto tokenize(std::string_view str) -> std::vector<Token>
    {
        std::vector<Token> tokens;

        return tokens;
    }
}