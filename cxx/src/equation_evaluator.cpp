#include "equation_evaluator.h"

#include "operations.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <deque>
#include <map>
#include <unordered_set>

#include <iostream>

using namespace EquationEvaluator;

namespace {

    constexpr std::array<std::string, 46> Token_Names{"(", ")", "==", "!=", "/=", "<=", ">=", "~=", "+", "-", 
                                                      "**", "*", "/", "^", "%", "&&", "||", "<<", ">>", "°", 
                                                      "!", "~", "min", "max", "pow", "mod", "rem", "round", "acos", "asin", 
                                                      "atan", "abs", "ln", "log", "exp", "floor", "ceiling", "&", "|", "cos",  
                                                      "sin", "tan", "ceil", "<", ">", ","};

    const std::unordered_set<char> Numeric_Tokens{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'e'};
    const std::unordered_set<char> Sign_Tokens{'-', '+'};
    const std::unordered_set<char> Additional_Symbol_Chars{'[', ']', '.', '*'};

    auto validSymbolCharacter(char c) -> bool
    {
        return isalnum(c) || Additional_Symbol_Chars.contains(c);
    }

    auto createMap() -> std::map<std::string_view, Token>
    {
        std::map<std::string_view, Token> tokens;

        tokens.emplace(std::make_pair(Token_Names.at(0), Token(Token_Names.at(0), Token::TokenType::Parenthesis)));
        tokens.emplace(std::make_pair(Token_Names.at(1), Token(Token_Names.at(1), Token::TokenType::Parenthesis)));
        tokens.emplace(std::make_pair(Token_Names.at(2), Token(Token_Names.at(2), Token::TokenType::Operator, &Operations::equals, 16, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(3), Token(Token_Names.at(3), Token::TokenType::Operator, &Operations::notEquals, 16, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(4), Token(Token_Names.at(4), Token::TokenType::Operator, &Operations::notEquals, 16, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(5), Token(Token_Names.at(5), Token::TokenType::Operator, &Operations::lessThanEquals, 9, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(6), Token(Token_Names.at(6), Token::TokenType::Operator, &Operations::greaterThanEquals, 9, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(7), Token(Token_Names.at(7), Token::TokenType::Operator, &Operations::approximatelyEquals, 16, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(8), Token(Token_Names.at(8), Token::TokenType::Operator, &Operations::plus, -1, -1)));
        tokens.emplace(std::make_pair(Token_Names.at(9), Token(Token_Names.at(9), Token::TokenType::Operator, &Operations::minus, -1, -1)));
        tokens.emplace(std::make_pair(Token_Names.at(10), Token(Token_Names.at(10), Token::TokenType::Operator, &Operations::power, 5, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(11), Token(Token_Names.at(11), Token::TokenType::Operator, &Operations::multiply, 5, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(12), Token(Token_Names.at(12), Token::TokenType::Operator, &Operations::divide, 5, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(13), Token(Token_Names.at(13), Token::TokenType::Operator, &Operations::bitwiseXor, 4, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(14), Token(Token_Names.at(14), Token::TokenType::Operator, &Operations::modulo, 5, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(15), Token(Token_Names.at(15), Token::TokenType::Operator, &Operations::logicalAnd, 14, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(16), Token(Token_Names.at(16), Token::TokenType::Operator, &Operations::logicalOr, 15, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(17), Token(Token_Names.at(17), Token::TokenType::Operator, &Operations::bitshiftLeft, 7, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(18), Token(Token_Names.at(18), Token::TokenType::Operator, &Operations::bitshiftRight, 7, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(19), Token(Token_Names.at(19), Token::TokenType::Operator, &Operations::degree, 3, 1, false)));
        tokens.emplace(std::make_pair(Token_Names.at(20), Token(Token_Names.at(20), Token::TokenType::Operator, &Operations::logicalNot, 3, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(21), Token(Token_Names.at(21), Token::TokenType::Operator, &Operations::bitwiseNot, 3, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(22), Token(Token_Names.at(22), Token::TokenType::Function, &Operations::min, 0, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(23), Token(Token_Names.at(23), Token::TokenType::Function, &Operations::max, 0, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(24), Token(Token_Names.at(24), Token::TokenType::Function, &Operations::power, 0, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(25), Token(Token_Names.at(25), Token::TokenType::Function, &Operations::modulo, 0, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(26), Token(Token_Names.at(26), Token::TokenType::Function, &Operations::remainder, 0, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(27), Token(Token_Names.at(27), Token::TokenType::Function, &Operations::round, 0, -1)));
        tokens.emplace(std::make_pair(Token_Names.at(28), Token(Token_Names.at(28), Token::TokenType::Function, &Operations::aCos, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(29), Token(Token_Names.at(29), Token::TokenType::Function, &Operations::aSin, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(30), Token(Token_Names.at(30), Token::TokenType::Function, &Operations::aTan, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(31), Token(Token_Names.at(31), Token::TokenType::Function, &Operations::abs, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(32), Token(Token_Names.at(32), Token::TokenType::Function, &Operations::ln, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(33), Token(Token_Names.at(33), Token::TokenType::Function, &Operations::log, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(34), Token(Token_Names.at(34), Token::TokenType::Function, &Operations::exp, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(35), Token(Token_Names.at(35), Token::TokenType::Function, &Operations::floor, 0, -1)));
        tokens.emplace(std::make_pair(Token_Names.at(36), Token(Token_Names.at(36), Token::TokenType::Function, &Operations::ceiling, 0, -1)));
        tokens.emplace(std::make_pair(Token_Names.at(37), Token(Token_Names.at(37), Token::TokenType::Operator, &Operations::bitwiseAnd, 11, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(38), Token(Token_Names.at(38), Token::TokenType::Operator, &Operations::bitwiseOr, 13, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(39), Token(Token_Names.at(39), Token::TokenType::Function, &Operations::cos, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(40), Token(Token_Names.at(40), Token::TokenType::Function, &Operations::sin, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(41), Token(Token_Names.at(41), Token::TokenType::Function, &Operations::tan, 0, 1)));
        tokens.emplace(std::make_pair(Token_Names.at(42), Token(Token_Names.at(42), Token::TokenType::Function, &Operations::ceiling, 0, -1)));
        tokens.emplace(std::make_pair(Token_Names.at(43), Token(Token_Names.at(43), Token::TokenType::Operator, &Operations::lessThan, 9, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(44), Token(Token_Names.at(44), Token::TokenType::Operator, &Operations::greaterThan, 9, 2)));
        tokens.emplace(std::make_pair(Token_Names.at(45), Token(Token_Names.at(45), Token::TokenType::Comma)));

        return tokens;
    } 

    auto createVariablePrecedences() -> std::map<std::string_view, std::array<int16_t, 2>>
    {
        std::map<std::string_view, std::array<int16_t, 2>> precedences;

        precedences[Token_Names.at(8)] = {3, 6};
        precedences[Token_Names.at(9)] = {3, 6};

        return precedences;
    }

    const std::map<std::string_view, std::array<int16_t, 2>> Variable_Precedences = createVariablePrecedences();
    const std::map<std::string_view, Token> Tokens = createMap();

    auto getUnknown(Token::TokenType type) -> std::unordered_set<std::string_view>
    {
        std::unordered_set<std::string_view> unknowns;
        for(auto && [name, token] : Tokens) {
            if(token.arity() < 0 && token.type() == type) {
                unknowns.insert(name);
            }
        }

        return unknowns;
    }

    const std::unordered_set<std::string_view> Unknown_Arity_Functions = getUnknown(Token::TokenType::Function);

    const std::map<std::string_view, std::array<int16_t, 2>> Ambiguous_Operators{{Token_Names.at(8), {2, 4}},
                                                                                 {Token_Names.at(9), {2, 4}}};

}

namespace EquationEvaluator {

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
        size_t prev_start = 1;
        size_t start = 0;
        size_t end = 0;

        while(start < str.size()) {

            // if we didn't find anything in the last loop, there may be an unknown symbol
            if(start == prev_start) {
                while(end < str.size() && validSymbolCharacter(str.at(end))) {
                    end++;
                }
                if(end > start) {
                    tokens.push_back(Token(str.substr(start, end-start), Token::TokenType::Symbol));
                    start = end;
                    previous_token_valueish = true;
                } else {
                    throw std::runtime_error("Unable to process rest of string");
                }
            } else {
                prev_start = start;
            }

            // gets values
            while(end < str.size() && (Numeric_Tokens.contains(str.at(end)) || isNumericSign(str, end))) {
                end++;
            }

            // add the value if we found one
            if(end > start) {
                tokens.push_back(Token(str.substr(start, end-start), Token::TokenType::Value));
                start = end;
                previous_token_valueish = true;
            }

            // look for additional tokens
            for(auto && name : Token_Names) {

                // the token names are in a very specific order, so we can look for them directly
                if((start + name.size()) <= str.size() && name == str.substr(start, name.size())) {
                    tokens.push_back(Tokens.at(name));
                    start += name.size();
                    end = start;
                    if(Ambiguous_Operators.contains(name)) {
                        auto & token = tokens.back();
                        token.setArity(previous_token_valueish ? 2 : 1);
                        token.setPrecedence(Variable_Precedences.at(token.text())[token.arity() - 1]);
                    }
                    previous_token_valueish = (name == ")" || name == ",");
                    break;
                }
            }
        }

        return tokens;
    }

    auto isLeftParenthesis(const Token & o2) -> bool
    {
        return o2.type() == Token::TokenType::Parenthesis && (o2.text() == "(");
    }

    auto popOperator(const Token & o1, const Token & o2) -> bool
    {
        return (!isLeftParenthesis(o2) && ((o2.precedence() > o1.precedence()) || (o2.precedence() == o1.precedence() && !o1.rightAssociative())));
    }

    void processOperator(Token token, std::deque<Token> & operator_stack, std::deque<Token> & queue)
    {
        while(popOperator(token, operator_stack.back())) {
            queue.push_back(operator_stack.back());
            operator_stack.pop_back();
        }
        operator_stack.push_back(token);
    }

    void processComma(Token token, std::deque<Token> & operator_stack, std::deque<Token> & queue)
    {
        while(!isLeftParenthesis(operator_stack.back())) {
            queue.push_back(operator_stack.back());
            operator_stack.pop_back();
        }
    }

    void processRightParenthesis(std::deque<Token> & operator_stack, std::deque<Token> & queue)
    {
        while(!isLeftParenthesis(operator_stack.back())) {
            queue.push_back(operator_stack.back());
            operator_stack.pop_back();
            if(operator_stack.empty()) {
                throw std::runtime_error("Unbalanced left and right parenthesis");
            }
        }
        operator_stack.pop_back();
        if(operator_stack.back().type() == Token::TokenType::Function) {
            queue.push_back(operator_stack.back());
            operator_stack.pop_back();
        }
    }

    // the actual shunting yard algorithm!
    auto parseTokens(const std::vector<Token> & tokens, ValueLookupFunc value_func) -> std::deque<Token>
    {
        std::deque<Token> operator_stack;
        std::deque<Token> queue;

        for(auto && token : tokens) {
            switch (token.type()) {
                case Token::TokenType::Value:   // intentional fall-through
                case Token::TokenType::Symbol:
                    queue.push_back(token);
                    break;
                case Token::TokenType::Function:
                    operator_stack.push_back(token);
                    break;
                case Token::TokenType::Operator:
                    processOperator(token, operator_stack, queue);
                    break;
                case Token::TokenType::Comma:
                    processComma(token, operator_stack, queue);
                    break;
                case Token::TokenType::Parenthesis:
                    if(isLeftParenthesis(token)) {
                        operator_stack.push_back(token);
                    } else {
                        processRightParenthesis(operator_stack, queue);
                    }
                    break;
            }
        }

        while(!operator_stack.empty()) {
            if(isLeftParenthesis(operator_stack.back())) {
                throw std::runtime_error("Unbalanced left and right parenthesis");
            }
            queue.push_back(operator_stack.back());
            operator_stack.pop_back();
        }

        return queue;
    }

    auto evaluate(std::string_view str, ValueLookupFunc value_func) -> ValueType
    {
        auto preprocessed = preprocess(str);
        auto tokens = tokenize(preprocessed);
        return ValueType(false);
    }
}

