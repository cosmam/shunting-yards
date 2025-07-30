#ifndef EQUATION_EVALUATOR_H
#define EQUATION_EVALUATOR_H

#include "token.h"

#include <string>
#include <vector>

namespace EquationEvaluator {

    auto preprocess(std::string_view str) -> std::string;

    auto tokenize(std::string_view str) -> std::vector<Token>;

    auto evaluate(std::string_view str, ValueLookupFunc value_func) -> ValueType;
}

#endif // EQUATION_EVALUATOR_H