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
#include <map>     // For map (key-value pairs)
#include <fstream> // For file input/output
#include <filesystem> // For filesystem operations (C++17 feature)
using namespace std; // Avoids having to write std:: before standard types

// Structure to store information about a single calculation
struct calculation {
    string operation, expression, result, timestamp;
};

// Basic arithmetic operation function declarations
double add(double x, double y); 
double sub(double x, double y); 
double div(double x, double y);
double multi(double x, double y); 
double mod(double x, double y); 
string div_print(double x, double y);

// Functions for saving and loading calculation history
void checkDatafile(vector<calculation>& history);
void createDatafile(vector<calculation>& history);
void save(vector<calculation>& history); 
void load(vector<calculation>& history);

// Functions for parsing and evaluating math expressions
bool parseAndCalculate(const string& input, vector<calculation>& history);
double evaluateExpression(const string& expr);
vector<string> tokenize(const string& expr);
vector<string> infixToPostfix(const vector<string>& tokens);
double evaluatePostfix(const vector<string>& postfix);
bool isOperator(const string& token);
int getPrecedence(const string& op);
bool isNumber(const string& s);

#endif