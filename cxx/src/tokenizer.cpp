#include "tokenizer.h"

#include <algorithm>
#include <map>
#include <unordered_set>

#include <iostream>

namespace {

    const std::vector<std::string> Token_Names{"(", ")", "+", "-", "*", "/", "^", "%", "&&", 
                                               "||", "<<", ">>", "°", "!", "~", "min", "max", "pow", "mod", 
                                               "rem", "round", "acos", "asin", "atan", "abs", "ln", "log", "floor", "ceiling", 
                                               "==", "!=", "/=", "<=", ">=", "~=", "&", "|", "cos", "sin", 
                                               "tan", "ceil", "<", ">"};

    const std::unordered_set<char> Numeric_Tokens{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'e'};
    const std::unordered_set<char> Skipped_Tokens{','};
    const std::unordered_set<char> Sign_Tokens{'-', '+'};
    const std::unordered_set<std::string_view> Unknown_Arity_Tokens{Token_Names.at(2), Token_Names.at(3)};

    auto createMap() -> std::map<std::string_view, Tokenizer::Token>
    {
        std::map<std::string_view, Tokenizer::Token> tokens;

        tokens[Token_Names.at(0)] = Tokenizer::Token(Token_Names.at(0), Tokenizer::TokenType::Parenthesis);
        tokens[Token_Names.at(1)] = Tokenizer::Token(Token_Names.at(1), Tokenizer::TokenType::Parenthesis);
        tokens[Token_Names.at(2)] = Tokenizer::Token(Token_Names.at(2), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(3)] = Tokenizer::Token(Token_Names.at(3), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(4)] = Tokenizer::Token(Token_Names.at(4), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(5)] = Tokenizer::Token(Token_Names.at(5), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(6)] = Tokenizer::Token(Token_Names.at(6), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(7)] = Tokenizer::Token(Token_Names.at(7), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(8)] = Tokenizer::Token(Token_Names.at(8), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(9)] = Tokenizer::Token(Token_Names.at(9), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(10)] = Tokenizer::Token(Token_Names.at(10), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(11)] = Tokenizer::Token(Token_Names.at(11), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(12)] = Tokenizer::Token(Token_Names.at(12), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(13)] = Tokenizer::Token(Token_Names.at(13), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(14)] = Tokenizer::Token(Token_Names.at(14), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(15)] = Tokenizer::Token(Token_Names.at(15), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(16)] = Tokenizer::Token(Token_Names.at(16), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(17)] = Tokenizer::Token(Token_Names.at(17), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(18)] = Tokenizer::Token(Token_Names.at(18), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(19)] = Tokenizer::Token(Token_Names.at(19), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(20)] = Tokenizer::Token(Token_Names.at(20), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(21)] = Tokenizer::Token(Token_Names.at(21), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(22)] = Tokenizer::Token(Token_Names.at(22), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(23)] = Tokenizer::Token(Token_Names.at(23), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(24)] = Tokenizer::Token(Token_Names.at(24), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(25)] = Tokenizer::Token(Token_Names.at(25), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(26)] = Tokenizer::Token(Token_Names.at(26), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(27)] = Tokenizer::Token(Token_Names.at(27), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(28)] = Tokenizer::Token(Token_Names.at(28), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(29)] = Tokenizer::Token(Token_Names.at(29), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(30)] = Tokenizer::Token(Token_Names.at(30), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(31)] = Tokenizer::Token(Token_Names.at(31), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(32)] = Tokenizer::Token(Token_Names.at(32), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(33)] = Tokenizer::Token(Token_Names.at(33), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(34)] = Tokenizer::Token(Token_Names.at(34), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(35)] = Tokenizer::Token(Token_Names.at(35), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(36)] = Tokenizer::Token(Token_Names.at(36), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(37)] = Tokenizer::Token(Token_Names.at(37), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(38)] = Tokenizer::Token(Token_Names.at(38), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(39)] = Tokenizer::Token(Token_Names.at(39), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(40)] = Tokenizer::Token(Token_Names.at(40), Tokenizer::TokenType::Function);
        tokens[Token_Names.at(41)] = Tokenizer::Token(Token_Names.at(41), Tokenizer::TokenType::Operator);
        tokens[Token_Names.at(42)] = Tokenizer::Token(Token_Names.at(42), Tokenizer::TokenType::Operator);

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

    auto isNumericSign(std::string_view s, size_t pos) -> bool
    {
        return (pos > 0 && Sign_Tokens.contains(s.at(pos)) && s.at(pos-1) == 'e');
    }

    auto tokenize(std::string_view str) -> std::vector<Token>
    {
        std::vector<Token> tokens;

        bool previous_token_valueish = false;
        size_t start = 0;
        size_t end = 0;

        while(end < str.size()) {
            while(end < str.size() && (Numeric_Tokens.contains(str.at(end)) || isNumericSign(str, end))) {
                end++;
            }
            if(end > start) {
                tokens.push_back(Token(str.substr(start, end-start), TokenType::Value));
                start = end;
                previous_token_valueish = true;
            }
            while(end < str.size() && Skipped_Tokens.contains(str.at(end))) {
                end++;
            }
            for(auto && name : Token_Names) {
                if((start + name.size()) <= str.size() && name == str.substr(start, name.size())) {
                    tokens.push_back(Tokens.at(name));
                    start += name.size();
                    end = start;
                    if(Unknown_Arity_Tokens.contains(name)) {
                        tokens.back().arity = (previous_token_valueish ? 2 : 1);
                    }
                    previous_token_valueish = (name == ")");
                    break;
                }
            }
        }

        return tokens;
    }
}