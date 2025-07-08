#ifndef CALC-HEADER_H_INCLUDED
#define CALC-HEADER_H_INCLUDED

/*
    =========================
    Standard library includes
    =========================
*/

#include <iostream>    // For input and output (cin, cout)
#include <string>      // For using the string type
#include <vector>      // For using the vector container
#include <cmath>       // For math functions like fmod, NAN
#include <cctype>      // For character handling (tolower, isdigit, etc.)
#include <limits>      // For numeric limits (like max stream size)
#include <sstream>     // For string streams (convert between strings and numbers)
#include <algorithm>   // For algorithms like sort, find, etc.
#include <stack>       // For stack data structure (used in expression evaluation)
#include <queue>       // For queue data structure
#include <map>         // For map (key-value pairs)
#include <fstream>     // For file input/output
#include <filesystem>  // For filesystem operations (C++17 feature)
using namespace std;   // Avoids having to write std:: before standard types

/*
    =========================
    OOP Class Declarations
    =========================
*/

// Represents a single calculation, including the operation, expression, result, and timestamp
class Calculation {
public:
    string operation;   // The type of operation performed (e.g., add, subtract, expression)
    string expression;  // The mathematical expression or operands used
    string result;      // The result of the calculation
    string timestamp;   // The date and time when the calculation was performed

    // Default constructor
    Calculation() = default;

    // Parameterized constructor
    Calculation(const string& op, const string& expr, const string& res, const string& time)
        : operation(op), expression(expr), result(res), timestamp(time) {}
};

// Manages the history of calculations, including saving, loading, and displaying
class CalculationHistory {
private:
    vector<Calculation> history; // Vector to store all calculations
public:
    // Checks if the data file and directory exist, creates/loads as needed
    void checkDatafile();
    // Creates a new data file with a header
    void createDatafile();
    // Saves the calculation history to the data file
    void save();
    // Loads the calculation history from the data file
    void load();
    // Adds a new calculation to the history
    void add(const Calculation& calc);
    // Clears the calculation history in memory
    void clear();
    // Returns true if the calculation history is empty
    bool empty() const;
    // Displays the calculation history to the console
    void display() const;
    // Returns a reference to the internal history vector
    vector<Calculation>& getHistory();
};

// Provides all calculator operations and expression parsing as static methods
class Calculator {
public:
    // Basic arithmetic operations
    static double add(double x, double y);           // Addition
    static double sub(double x, double y);           // Subtraction
    static double div(double x, double y);           // Division (with zero/finite checks)
    static double multi(double x, double y);         // Multiplication
    static double mod(double x, double y);           // Modulus (with zero/finite checks)
    static string div_print(double x, double y);     // Returns quotient and remainder as string
    static double pow(double base, double exponent); // Exponentiation (with error checks)

    // Expression parsing and evaluation
    static bool parseAndCalculate(const string& input, CalculationHistory& history); // Parses and calculates an expression, adds to history
    static double evaluateExpression(const string& expr);                            // Evaluates a math expression string
    static vector<string> tokenize(const string& expr);                              // Tokenizes a math expression string
    static vector<string> infixToPostfix(const vector<string>& tokens);              // Converts infix tokens to postfix (RPN)
    static double evaluatePostfix(const vector<string>& postfix);                    // Evaluates a postfix expression

    // Utility functions for parsing
    static bool isOperator(const string& token);     // Checks if a string is an operator
    static int getPrecedence(const string& op);      // Gets the precedence of an operator
    static bool isNumber(const string& s);           // Checks if a string is a valid number
};

#endif // CALC-HEADER_H_INCLUDED