# ToyProgrammingLanguage
Creation of a toy programming language: Blip

The language has straight-line code consisting of assignment statements and output statements. Made to be very easy to parse, bears no resemblance to any real programming language

Four language statements: var, set, output, and text
1. var statements intialize a new variable. If a var statement specifies a variable already created, Blip generates a warning. Examples of legal var expressions: var x 42; var y + x 1
2. set statements are similar to var statements, except it should be used to re-assign a new value to an existing variable. If a set statement specifies a variable dthat does not already exist, Blip generates a warning. Regardless of whether the warning message is created, the result of a set statement is to ensure that there is a variable in the Blip internal memory with the specified value. Examples of legal set expressions: set x 42; set x + x 1
3. text statements result in a text message being displayed on the screen. Can be a single word or a quoted string. Examples of legal text statements: text Hello; text "Hello World".
4. output statements result in a number being displayed on the screen. Examples of legal output statements: output 42; output + 1 1; output * x x; output + * x x * y y


Implementation of variables is done through use of a symbol table

Blip expressions: 

Binary math operators: +, -, *, /, %
Binary logic operators: &&, ||
Comparison Operators: <, >, ==, !=, <=, >= Unary Operators: !, ~
