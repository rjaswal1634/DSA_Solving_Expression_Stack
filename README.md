This code implements a C++ program that evaluates postfix expressions using stacks. It can handle basic arithmetic operations (+, -, *, /) and parentheses for proper order of evaluation.
The Requirements for the code is Explained in the Pdf. 
Key Features:

Evaluates postfix expressions using stacks for numbers and operators.
Supports basic arithmetic operations (+, -, *, /).
Handles parentheses for correct evaluation order.
Includes error handling for invalid expressions (division by zero, missing parentheses, invalid characters).
How it Works:

The code reads the expression string token by token.
It checks if the token is a number:
If it is, it pushes the converted integer value (using stoi) onto the numbers stack.
If the token is a left parenthesis ("("):
It pushes the '(' character onto the operators stack.
If the token is a right parenthesis (")"):
It keeps evaluating the top elements of the stacks until it encounters a left parenthesis. This ensures proper order of operations.
If there's no matching left parenthesis or the expression is invalid, it throws an exception.
If the token is an operator (+, -, *, /):
It keeps evaluating operators on the operators stack with higher or equal precedence than the current operator.
Then, it pushes the current operator onto the operators stack.
For any other character (invalid input), it throws an exception.
After processing the entire expression, it ensures there's only one element left on the numbers stack (the final result).
If there are more elements or no elements, it throws an exception indicating an invalid expression.
Error Handling:

The code throws invalid_argument exceptions for various error scenarios, providing informative messages in the catch block.
Sample Runs and Test Cases:

A separate PDF file (Test Cases & Output) provides sample runs and test cases demonstrating the program's behavior with different expressions.

Getting Started:
Compile the code using a C++ compiler (e.g., g++).
Run the executable and observe the output.
Refer to the PDF file for detailed test cases and expected results.
