#include <iostream>
#include <string>

#include "equation_evaluator.h"

auto valueLookup(std::string_view str) -> ValueType
{
    return ValueType(0.0);
}

void print(const ValueType & value)
{
    if(value.holdsAlternative<double>()) {
        std::cout << value.get<double>() << std::endl;
    } else if(value.holdsAlternative<int64_t>()) {
        std::cout << value.get<int64_t>() << std::endl;
    } else {
        std::cout << (value.get<bool>() ? "true" : "false") << std::endl;
    }
}

int main() {
    std::cout << "Enter equation:" << std::endl;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        print(EquationEvaluator::evaluate(line, &valueLookup));
    }

    return 0; // Indicates successful execution
}