#!/usr/bin/python3

from enum import Enum

replacements = {"**": "^"}
supported_symbols = ["(", ")", "+", "-", "*", "/", "^"]

class Operator(Enum):
    ADDITION = 1
    SUBTRACTION = 2
    MULTIPLICATION = 3
    DIVISION = 4
    EXPONENTIATION = 5
    LEFT_PAREN = 6
    RIGHT_PAREN = 7

base_operators = [Operator.ADDITION, Operator.SUBTRACTION, Operator.MULTIPLICATION, Operator.DIVISION, Operator.EXPONENTIATION]
operator_precedence = {Operator.ADDITION: 1,
                       Operator.SUBTRACTION: 1,
                       Operator.MULTIPLICATION: 2,
                       Operator.DIVISION: 2,
                       Operator.EXPONENTIATION: 3,
                       Operator.LEFT_PAREN: 4,
                       Operator.RIGHT_PAREN: 4}

operator_chars = {"+": Operator.ADDITION,
                  "-": Operator.SUBTRACTION,
                  "*": Operator.MULTIPLICATION,
                  "/": Operator.DIVISION,
                  "^": Operator.EXPONENTIATION,
                  "(": Operator.LEFT_PAREN,
                  ")": Operator.RIGHT_PAREN}

def _add(a, b):
    return a + b


def _subtract(a, b):
    return a - b


def _multiply(a, b):
    return a * b


def _divide(a, b):
    return a / b


def _exp(a, b):
    return a ** b


operator_funcs = {Operator.ADDITION: _add,
                  Operator.SUBTRACTION: _subtract,
                  Operator.MULTIPLICATION: _multiply,
                  Operator.DIVISION: _divide,
                  Operator.EXPONENTIATION: _exp}

def _cleanupMinus(text):
    i=0
    while(i < len(text)):
        if text[i] == "-" and i > 0:
            if text[i-1] in supported_symbols or text[i+1] == "-":
                text = text[:i] + " -" + text[i+1:]
                i += 1
            else:
                text = text[:i] + " - " + text[i+1:]
                i += 2
        i += 1
    return text


def _tokenize(text):
    for k, v in replacements.items():
        text = text.replace(k, v)
    text = "".join(text.split())
    text = _cleanupMinus(text)
    for symbol in [s for s in supported_symbols if s != "-"]:    # for simplicity, make sure each symbol is a token
        text = text.replace(symbol, f' {symbol} ')
    return list(filter(None, text.split()))


def is_int_tryexcept(s):
    """ Returns True if string is a number. """
    try:
        int(s)
        return True
    except ValueError:
        return False


def is_float_tryexcept(s):
    """ Returns True if string is a number. """
    try:
        float(s)
        return True
    except ValueError:
        return False
    

def _isNumber(token):
    return is_int_tryexcept(token) or is_float_tryexcept(token)


def _getNumber(token):
    if is_int_tryexcept(token):
        return int(token)
    elif is_float_tryexcept(token):
        return float(token)
    return None


def _parseTokens(tokens):
    operator_stack = []
    queue = []
    for token in tokens:
        if _isNumber(token):
            queue.append(_getNumber(token))
        elif token in supported_symbols:
            operator = operator_chars[token]
            if operator == Operator.LEFT_PAREN:
                operator_stack.append(operator)
            elif operator == Operator.RIGHT_PAREN:
                while len(operator_stack) > 0 and operator_stack[-1] != Operator.LEFT_PAREN:
                    queue.append(operator_stack[-1])
                    operator_stack = operator_stack[:-1]
                operator_stack = operator_stack[:-1]
            else:
                if len(operator_stack) > 0 and operator_stack[-1] != Operator.LEFT_PAREN and operator_precedence[operator_stack[-1]] > operator_precedence[operator]:
                    queue.append(operator_stack[-1])
                    operator_stack[-1] = operator
                else:
                    operator_stack.append(operator)
    while len(operator_stack) > 0:
        queue.append(operator_stack[-1])
        operator_stack = operator_stack[:-1]
    return queue


def _evaluate(queue):
    stack = []
    for t in queue:
        if isinstance(t, Operator):
            a = stack[-2]
            b = stack[-1]
            stack = stack[:-2]
            stack.append(operator_funcs[t](a, b))
        else:
            stack.append(t)
    return stack[0]


def compute(text):
    if text.count("(") != text.count(")"):
        raise ValueError("Unmatched parenthesis")
    queue = _parseTokens(_tokenize(text))
    return _evaluate(queue)