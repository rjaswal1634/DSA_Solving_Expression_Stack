// Rahul Chaudhari
// Using Stack to Evaluate Expression & Parse it 
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctype.h>

using namespace std;
/**
 * Checks if a given string represents a valid number.
 * @param s The string to be checked.
 * @return True if the string represents a valid number, false otherwise.
 */
bool isNumber(const string &s);

/**
 * Determines the precedence level of an operator.
 *
 * @param op The operator character.
 * @return The precedence level of the operator.
 */
int precedence(char op);

/**
 * Applies the given operator to the provided operands.
 * @param left  The left operand.
 * @param op    The operator character.
 * @param right The right operand.
 * @return The result of applying the operator to the operands.
 * @throws invalid_argument If the operator is invalid or division by zero occurs.
 */
int applyOperator(int left, char op, int right);

/**
 * Evaluates the topmost operation in the stacks of numbers and operators.
 * @param numbers   Stack of numbers.
 * @param operators Stack of operators.
 * @throws invalid_argument If the expression is invalid.
 */
void evaluateTop(stack<int> &numbers, stack<char> &operators);

/**
 * Evaluates a mathematical expression represented as a string.
 *
 * @param expression The mathematical expression to be evaluated.
 * @return The result of the evaluation.
 * @throws invalid_argument respective error
 */
int evaluate(string expression);


int main()
{
  // trying the 1st case
  try
  {
    cout << evaluate("3 x ( ( ( 4 + 5 ) / 3 ) * ( 20 + 1 ) )") << endl;
  }
  catch (const exception &e)
  {
    cout << "3 x ( ( ( 4 + 5 ) / 3 ) * ( 20 + 1 ) ) ERROR: " << e.what() << endl;
  }

  // trying the 2nd case
  try
  {
    cout << evaluate("3 x ( ( ( 4b + 5 ) / 3 ) * ( 20 + 1 ) ) ") << endl;
  }
  catch (const exception &e)
  {
    cout << "3 x ( ( ( 4b + 5 ) / 3 ) * ( 20 + 1 ) )  ERROR: " << e.what() << endl;
  }

  // trying the 3rd case
  try
  {
    cout << evaluate("3 x ( ( ( 4 + 5 ) / 3 ) * ( 20 + 1 )") << endl;
  }
  catch (const exception &e)
  {
    cout << "3 x ( ( ( 4 + 5 ) / 3 ) * ( 20 + 1 ) ERROR: " << e.what() << endl;
  }

  // trying the 4th case
  try
  {
    cout << evaluate("3 x ( ( ( 4 < 5 ) / 3 ) * ( 20 + 1 ) )") << endl;
  }
  catch (const exception &e)
  {
    cout << "3 x ( ( ( 4 < 5 ) / 3 ) * ( 20 + 1 ) ) ERROR: " << e.what() << endl;
  }
  try
  {
    cout << evaluate("7 x ( 4 + 3 )") << endl;
  }
  catch (const exception &e)
  {
    cout << "7 x ( 4 + 3 ) ERROR: " << e.what() << endl;
  }
    // Add more test cases here...
    return 0;
}

// function to check a string is number or not
bool isNumber(const string &s)
{
  for (char c : s)
  {
    if (!isdigit(c))
    {
      return false;
    }
  }
  return !s.empty();
}


// function to check the precedence
int precedence(char op)
{
  switch (op)
  {
    case '+':
    case '-':
    return 1;
    case '*':
    case 'x':
    case '/':
    return 2;
    default:
    return -1;
    }
}

//function to apply the operation
int applyOperator(int left, char op, int right)
{
  switch (op)
  {
    case '+':
    return left + right;
    case '-':
    return left - right;
    case '*':
    case 'x':
    return left * right;
    case '/':
    if (right == 0) throw invalid_argument("division by zero");
    return left / right;
    default:
    throw invalid_argument("invalid operator(s)");
  }
}

// function to evaluate the top
void evaluateTop(stack<int> &numbers, stack<char> &operators)
{
  if (numbers.size() < 2 || operators.empty())
  {
    throw invalid_argument("invalid expression");
  }
  int right = numbers.top(); numbers.pop();
  int left = numbers.top(); numbers.pop();
  char op = operators.top(); operators.pop();
  numbers.push(applyOperator(left, op, right));
}

// function to evaluate the expression
int evaluate(string expression)
{
  stack<int> numbers;
  stack<char> operators;
  stringstream input_string(expression);
  string token;

  while (input_string >> token)
  {
    if (isNumber(token))
    {
      numbers.push(stoi(token));
    }
    else if (token == "(")
    {
      operators.push('(');
    }
    else if (token == ")")
    {
      while (!operators.empty() && operators.top() != '(')
      {
        evaluateTop(numbers, operators);
      }
      if (operators.empty() || operators.top() != '(')
      {
        throw invalid_argument("invalid expression");
      }
      operators.pop();
    }
    else if (ispunct(token[0]) || isalpha(tolower((token[0]))))
    {
      while (!operators.empty() && precedence(operators.top()) >= precedence(token[0]))
      {
        evaluateTop(numbers, operators);
      }
      operators.push(token[0]);
    }
    else
    {
      throw invalid_argument("invalid number(s)");
    }
  }

  while (!operators.empty())
  {
    if (operators.top() == '(')
    {
      throw invalid_argument("invalid expression");
    }
    evaluateTop(numbers, operators);
  }
  if (numbers.size() != 1)
  {
    throw invalid_argument("invalid expression");
  }
  return numbers.top();
}
