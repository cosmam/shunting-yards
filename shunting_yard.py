#!/usr/bin/python3

replacements = {"**": "^"}
supported_symbols = ["(", ")", "+", "*", "/", "^"]


def _cleanupMinus(text):
    return text


def _tokenize(text):
    for k, v in replacements.items():
        text = text.replace(k, v)
    text = "".join(text.split())
    text = _cleanupMinus(text)
    for symbol in supported_symbols:    # for simplicity, make sure each symbol is a token
        text = text.replace(symbol, f' {symbol} ')
    return list(filter(None, text.split()))


def compute(text):
    tokens = _tokenize(text)
    return 0