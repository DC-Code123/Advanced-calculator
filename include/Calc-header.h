#ifndef CALC_HEADER_H
#define CALC_HEADER_H

// Standard library includes for common C++ features
#include <iostream> // For input and output (cin, cout)
#include <string>   // For using the string type
#include <vector>   // For using the vector container
#include <cmath>    // For math functions like fmod, NAN
#include <cctype>   // For character handling (tolower, isdigit, etc.)
#include <limits>   // For numeric limits (like max stream size)
#include <sstream>  // For string streams (convert between strings and numbers)
#include <algorithm> // For algorithms like sort, find, etc.
#include <stack>    // For stack data structure (used in expression evaluation)
#include <queue>    // For queue data structure
#include <map>      // For map (key-value pairs)
using namespace std; // Avoids having to write std:: before standard types

// Structure to store information about a single calculation
// Contains the operation performed, the expression, the result, and the time it was done
struct calculation {
    string operation;   // The type of operation (e.g., add, subtract, etc.)
    string expression;  // The full math expression as a string (e.g., "2 + 2")
    string result;      // The result of the calculation as a string
    string timestamp;   // The date and time when the calculation was performed
};

// Basic arithmetic operation function declarations
double add(double x, double y);      // Returns the sum of x and y
double sub(double x, double y);      // Returns the difference of x and y
double div(double x, double y);      // Returns the result of x divided by y (handles division by zero)
double multi(double x, double y);    // Returns the product of x and y
double mod(double x, double y);      // Returns the remainder of x divided by y (handles division by zero)
string div_print(double x, double y);// Returns a string showing quotient and remainder

// Functions for parsing and evaluating math expressions
bool parseAndCalculate(const string& input, vector<calculation>& history); // Parses a string, calculates the result, and stores it in history
double evaluateExpression(const string& expr); // Evaluates a math expression string and returns the result
vector<string> tokenize(const string& expr);   // Splits an expression string into tokens (numbers, operators, etc.)
vector<string> infixToPostfix(const vector<string>& tokens); // Converts infix tokens to postfix (RPN) for easier evaluation
double evaluatePostfix(const vector<string>& postfix); // Evaluates a postfix (RPN) expression and returns the result
bool isOperator(const string& token); // Returns true if the token is a math operator
int getPrecedence(const string& op);  // Returns the precedence of a math operator
bool isNumber(const string& s);       // Returns true if the string is a valid number

#endif