A repo for me to play around with implementations of the Shunting Yard Algorithm! And possibly related cases, depending on how long my attention holds.

## Tokens to Parse

Broadly speaking, there are four categories of things to parse: numbers, operators, functions, and mistakes. Details are presented below

### Numbers

For maximum flexibility, I intend to support: integers, decimals, and scientific notation (e or E).

### Operators

Should allow for binary operators, with both left- and right-precedence if possible, and unary operators. A non-exhaustive list is:
* Binary operators: +, -, *, /, ^, %
* Unary operators: +, -
* Stretch goal binary operators: &, &&, |, ||, <<, >>
* Stretch goal unary operators: |x|, °, !, ~

### Functions

Should allow for binary and unary functions.
* Binary functions: min, max, pow, rem
* Unary functions: cos, sin, tan, acos, asin, atan, abs, ln, log

### Mistakes

Anything not in the above.
