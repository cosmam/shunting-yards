#!/usr/bin/python3

import itertools
import random
from enum import Enum, Flag, auto


#A.BeC, where A, B, and D are integers and C is one of E or E

class Spaces(Flag):
    NONE = 0
    BEFORE = auto()
    AFTER = auto()

class NumberFormat(Flag):
    A = auto()
    B = auto()
    B0 = auto()
    C = auto()

number_formats = [NumberFormat.A, 
                  NumberFormat.B, 
                  NumberFormat.B0,
                  NumberFormat.A | NumberFormat.B, 
                  NumberFormat.A | NumberFormat.C, 
                  NumberFormat.B | NumberFormat.C,
                  NumberFormat.B0 | NumberFormat.C, 
                  NumberFormat.A | NumberFormat.B | NumberFormat.C]

space_formats = [Spaces.NONE, Spaces.BEFORE, Spaces.AFTER, Spaces.BEFORE | Spaces.AFTER]

unary_operators = ["+", "-", "!", "~"]
binary_operators = ["+", "-", "*", "/", "^", "%", "&", "|", "<<", ">>"]
unary_functions = ["round", "acos", "asin", "atan", "abs", "ln", "log", "floor", "ceiling", "cos", "sin", "tan", "ceil"]
binary_functions = ["min", "max", "pow", "mod", "rem", "ceiling", "ceil", "floor", "round"]
comparison_operators = ["==", "!=", "/=", "<=", ">=", "~=", "&&", "||", "<", ">"]


def _write(lines, outfile):
    with open(outfile, "a") as f:
        for l in lines:
            f.write(l + '\n')


def _get_spaces(space_format):
    return [" " if Spaces.BEFORE in space_format else "", " " if Spaces.AFTER in space_format else ""]


def _generate_number(number_format):
    number = ""
    if NumberFormat.A in number_format:
        number = number + str(random.randrange(1, 200))
    if NumberFormat.B in number_format:
        number = number + "." + str(random.randrange(1, 200))
    if NumberFormat.B0 in number_format:
        number = number + "0." + str(random.randrange(1, 200))
    if NumberFormat.C in number_format:
        exponent = random.randrange(-10, 10)
        sign = "+" if exponent > 0 and (random.randrange(1, 200) % 2 == 0) else ""
        number = number + ("e" if random.randrange(1, 200) % 2 == 0 else "E") + sign + str(exponent)
    return number


def _generate_unary_operator(operator, operator_spaces, number_format, number_spaces):
    pieces = _get_spaces(operator_spaces) + _get_spaces(number_spaces)
    pieces.insert(1, operator)
    pieces.insert(4, _generate_number(number_format))
    return f'{"".join(pieces)};{operator},{pieces[4].lower()}'


def _generate_unary_function(function, function_spaces, number_format, number_spaces):
    pieces = _get_spaces(function_spaces) + _get_spaces(number_spaces)
    pieces.insert(1, function + "(")
    pieces.insert(4, _generate_number(number_format))
    pieces.append(")")
    return f'{"".join(pieces)};{function},(,{pieces[4].lower()},)'


def _generate_binary_operator(number_format_one, number_spaces_one, operator, operator_spaces, number_format_two, number_spaces_two):
    pieces = _get_spaces(number_spaces_one) + _get_spaces(operator_spaces) + _get_spaces(number_spaces_two)
    pieces.insert(1, _generate_number(number_format_one))
    pieces.insert(4, operator)
    pieces.insert(7, _generate_number(number_format_two))
    return f'{"".join(pieces)};{pieces[1].lower()},{operator},{pieces[7].lower()}'


def _generate_binary_function(number_format_one, number_spaces_one, function, function_spaces, number_format_two, number_spaces_two):
    pieces = _get_spaces(function_spaces) + _get_spaces(number_spaces_one) + _get_spaces(number_spaces_two)
    pieces.insert(1, function + "(")
    pieces.insert(4, _generate_number(number_format_one))
    pieces.insert(6, ",")
    pieces.insert(8, _generate_number(number_format_two))
    pieces.append(")")
    return f'{"".join(pieces)};{function},(,{pieces[4].lower()},{pieces[8].lower()},)'


def _generate_unary_operators():
    data = []
    for x in itertools.product(unary_operators, space_formats, number_formats, space_formats):
        data.append(_generate_unary_operator(x[0], x[1], x[2], x[3]))
    return data


def _generate_unary_functions():
    data = []
    for x in itertools.product(unary_functions, space_formats, number_formats, space_formats):
        data.append(_generate_unary_function(x[0], x[1], x[2], x[3]))
    return data


def _generate_binary_operators():
    data = []
    for x in itertools.product(number_formats, space_formats, binary_operators, space_formats, number_formats, space_formats):
        data.append(_generate_binary_operator(x[0], x[1], x[2], x[3], x[4], x[5]))
    return data


def _generate_binary_functions():
    data = []
    for x in itertools.product(number_formats, space_formats, binary_functions, space_formats, number_formats, space_formats):
        data.append(_generate_binary_function(x[0], x[1], x[2], x[3], x[4], x[5]))
    return data


def _generate_comparison_operators():
    data = []
    for x in itertools.product(number_formats, space_formats, comparison_operators, space_formats, number_formats, space_formats):
        data.append(_generate_binary_operator(x[0], x[1], x[2], x[3], x[4], x[5]))
    return data


def _output_singles(outfile, count):
    for _ in range(count):
        lines = []
        lines.extend(_generate_unary_operators())
        lines.extend(_generate_binary_operators())
        lines.extend(_generate_unary_functions())
        lines.extend(_generate_binary_functions())
        lines.extend(_generate_comparison_operators())
        _write(lines, outfile)


if __name__ == "__main__":
    _output_singles("./test_data/single_values.dat", 5)