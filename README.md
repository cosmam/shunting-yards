A repo for me to play around with implementations of the Shunting Yard Algorithm! And possibly related cases, depending on how long my attention holds.

## Backgroud Assumptions

Any constants have already been replaced with their numerical values. So, for instance, neither pi nor π will be in the equation to evaluate; it will already have been replaced with 3.14159

Whitespace has no effect.

## Tokens to Parse

Broadly speaking, there are four categories of things to parse: numbers, operators, functions, and mistakes. Details are presented below

### Numbers

For maximum flexibility, I intend to support: integers, decimals, and scientific notation (e or E). Signs will be handled by unary operators

### Operators

Should allow for binary operators, with both left- and right-precedence if possible, and unary operators. A non-exhaustive list is:
* Binary operators: +, -, *, /, ^, %
* Unary operators: +, -
* Stretch goal binary operators: &, &&, |, ||, <<, >>
* Stretch goal unary operators: °, !, ~

### Functions

Should allow for binary and unary functions.
* Binary functions: min, max, pow, mod, rem, round
* Unary functions: cos, sin, tan, acos, asin, atan, abs, ln, log, floor, ceiling

### Mistakes

Anything not in the above.

## Super-Mega-Extra Stretch Goal

Support equality operators. Evaluate both sides of the equation, then the operator, and return True or False

Operators: ==, !=, /=, <=, >=, <, >, ~=

## Testing

Testing will be driven by files with a comma-separated string and number (except for the error cases), where a correct evaluation of the string yields the numerical value.

### Number Formats

Valid number format is: [A][.B][C][D]. At least one of A and B is required; iIf C or D is defined, the other must be.

A: Any valid string of numbers. 1, 123, 000001, 100000
B: A period followed by a valid string of numbers
C: Either 'e' or 'E'
D: Optionally, a sign, followed by digits (decimal not allowed). so "00001", "+12", "-00001", "-123"
