#!/usr/bin/python3

import itertools
import shunting_yard
import unittest


operator_chars = {shunting_yard.Operator.ADDITION: "+",
                  shunting_yard.Operator.SUBTRACTION: "-",
                  shunting_yard.Operator.MULTIPLICATION: "*",
                  shunting_yard.Operator.DIVISION: "/",
                  shunting_yard.Operator.EXPONENTIATION: "^"}

class TestCalculation(unittest.TestCase):

    def testSimpleCalculations(self):
        for d in _getSimpleCalculationsData():
            with self.subTest(d=d):
                self.assertEqual(shunting_yard.compute(d[0]), d[1])

    def testOperatorPrecedence(self):
        for d in _getCompoundCalculationData():
            with self.subTest(d=d):
                self.assertEqual(shunting_yard.compute(d[0]), d[1])

    def testOtherCalcs(self):
        for d in _getOtherCalculationData():
            with self.subTest(d=d):
                self.assertEqual(shunting_yard.compute(d[0]), d[1])

def _isIllegalExponentiation(op, value_pair):
    return op == shunting_yard.Operator.EXPONENTIATION and value_pair[0] < 0 and isinstance(value_pair[1], float)


def _pareOperations(operations):
    pared = []
    for p in operations:
        if not _isIllegalExponentiation(p[0], p[1]):
            pared.append(p)
    return pared


def _pareCompoundOperations(operations):
    pared = []
    for p in operations:
        if not (_isIllegalExponentiation(p[0][0], (p[1][0], p[1][1])) or _isIllegalExponentiation(p[0][0], (p[1][0], p[1][1]))):
            pared.append(p)
    return pared


def _getOperators(op):
    operators = []
    text = operator_chars[op]
    operators.append(text)
    operators.append(" " + text)
    operators.append(text + " ")
    operators.append(" " + text + " ")
    return operators


def _getSimpleCalculationsData():
    data = []
    raw_values = [1, 4, 21, 17, -2, -8, -13, -22, 2.1, 3.12513, 10.910, 12.18913, -2.0, -6.123, -20.123, -18.1230192]
    value_pairs = itertools.product(raw_values, raw_values)
    for op, vals in _pareOperations(list(itertools.product(shunting_yard.base_operators, value_pairs))):
        for op_text in _getOperators(op):
            result = shunting_yard.operator_funcs[op](vals[0], vals[1])
            text = str(vals[0]) + op_text + str(vals[1])
            data.append((text, result))
    return data


def _getCompoundCalculationData():
    data = []
    raw_values = [1, 4, 10, -2, -8, -13, 2.1, 3.12513, 10.910, 12.18913, -2.0, -6.123, -11.1230192]
    value_triplets = list(itertools.product(raw_values, raw_values, raw_values))
    op_pairs = list(itertools.product(shunting_yard.base_operators, shunting_yard.base_operators))
    for ops, vals in _pareCompoundOperations(list(itertools.product(op_pairs, value_triplets))):
        for op_texts in list(itertools.product(_getOperators(ops[0]), _getOperators(ops[1]))):
            result = None
            if shunting_yard.operator_precedence[ops[0]] < shunting_yard.operator_precedence[ops[1]]:
                result = shunting_yard.operator_funcs[ops[0]](vals[0], shunting_yard.operator_funcs[ops[1]](vals[1], vals[2]))
            else:
                result = shunting_yard.operator_funcs[ops[1]](shunting_yard.operator_funcs[ops[0]](vals[0], vals[1]), vals[2])
            text = str(vals[0]) + op_texts[0] + str(vals[1]) + op_texts[1] + str(vals[2])
            data.append((text, result))
    return data


if __name__ == "__main__":
    unittest.main()