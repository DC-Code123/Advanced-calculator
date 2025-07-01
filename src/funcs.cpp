#include "../include/Calc-header.h"

// These are our math games!
// Adds two numbers and returns the result
double add(double x, double y) { return x + y; } // Add two numbers
// Subtracts the second number from the first
double sub(double x, double y) { return x - y; } // Take one number away from another

// Divides x by y and returns the result. If y is zero, prints an error and returns NaN.
double div(double x, double y) {
    if (y == 0) {
        cout << "Error: Division by zero" << endl; // Can't share with zero friends!
        return NAN; // Not a number if we can't do it
    }
    return x / y; // Share the numbers
}

// Multiplies two numbers and returns the result
double multi(double x, double y) { return x * y; } // Make groups of things (multiply)

// Returns the remainder of x divided by y. If y is zero, prints an error and returns NaN.
double mod(double x, double y) {
    if (y == 0) {
        cout << "Error: Modulus by zero" << endl; // Can't find leftovers if we don't share!
        return NAN;
    }
    return fmod(x, y); // Find the leftovers
}

// Returns a string showing the quotient and remainder of x divided by y
string div_print(double x, double y) {
    if (y == 0) return "Error: Division by zero"; // Can't share with zero
    double quotient = div(x, y); // How many times we can share
    double remainder = mod(x, y); // What's left after sharing
    return to_string(quotient) + " R " + to_string(remainder); // Say the answer
}

// Checks if a string is a number (returns true if it is, false otherwise)
// Is this a number? Let's check!
bool isNumber(const string& s) {
    try {
        stod(s); // Try to turn it into a number
        return true; // Yay, it's a number!
    } catch (...) {
        return false; // Nope, not a number
    }
}

// Checks if a string is a math operator (+, -, *, /, %)
// Is this a math sign? (+, -, *, /, %)
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

// Returns the precedence of a math operator (higher number = higher precedence)
// Which math sign is more important?
int getPrecedence(const string& op) {
    if (op == "+" || op == "-") return 1; // + and - are not as important
    if (op == "*" || op == "/" || op == "%") return 2; // *, /, % are more important
    return 0;
}

// Splits a math expression into tokens (numbers and operators)
// Break our math sentence into little pieces
vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string current;
    
    for (char c : expr) {
        if (isspace(c)) continue; // Skip spaces
        
        if (isdigit(c) || c == '.') {
            current += c; // Make a number
        } else if (c == '(' || c == ')') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            tokens.push_back(string(1, c)); // Add the bracket
        } else if (isOperator(string(1, c))) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            // If we see a minus sign in a special spot, it's a negative number!
            if (c == '-' && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()))) {
                current += c;
            } else {
                tokens.push_back(string(1, c)); // Add the math sign
            }
        }
    }
    
    if (!current.empty()) {
        tokens.push_back(current); // Add the last number
    }
    
    return tokens;
}

// Converts infix notation (normal math) to postfix notation (easier for computers to solve)
// Change our math sentence to a special order (postfix) so it's easy to solve
vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> postfix;
    stack<string> opStack;
    
    for (const string& token : tokens) {
        if (isNumber(token)) {
            postfix.push_back(token); // Numbers go right in line
        } else if (token == "(") {
            opStack.push(token); // Save the open bracket
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                postfix.push_back(opStack.top()); // Move math signs out
                opStack.pop();
            }
            opStack.pop(); // Take away the open bracket
        } else if (isOperator(token)) {
            while (!opStack.empty() && getPrecedence(opStack.top()) >= getPrecedence(token)) {
                postfix.push_back(opStack.top()); // Move more important math signs out
                opStack.pop();
            }
            opStack.push(token); // Save this math sign
        }
    }
    
    while (!opStack.empty()) {
        postfix.push_back(opStack.top()); // Move any leftover math signs
        opStack.pop();
    }
    
    return postfix;
}

// Evaluate postfix expression
double evaluatePostfix(const vector<string>& postfix) {
    stack<double> valStack;
    
    for (const string& token : postfix) {
        if (isNumber(token)) {
            valStack.push(stod(token));
        } else if (isOperator(token)) {
            if (valStack.size() < 2) {
                throw runtime_error("Invalid expression: not enough operands");
            }
            
            double b = valStack.top(); valStack.pop();
            double a = valStack.top(); valStack.pop();
            double result;
            
            if (token == "+") result = add(a, b);
            else if (token == "-") result = sub(a, b);
            else if (token == "*") result = multi(a, b);
            else if (token == "/") result = div(a, b);
            else if (token == "%") result = mod(a, b);
            
            valStack.push(result);
        }
    }
    
    if (valStack.size() != 1) {
        throw runtime_error("Invalid expression");
    }
    
    return valStack.top();
}

// Evaluate a mathematical expression
double evaluateExpression(const string& expr) {
    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

// Parse input and perform calculation
bool parseAndCalculate(const string& input, vector<calculation>& history) {
    try {
        // Check for simple commands first
        if (input.empty()) return false;
        
        // Evaluate the expression
        double result = evaluateExpression(input);
        
        if (isnan(result)) {
            cout << "Calculation error occurred" << endl;
            return false;
        }
        
        // Store in history
        calculation calc;
        calc.operation = "expression";
        calc.expression = input;
        calc.result = to_string(result);
        calc.timestamp = __DATE__ " " __TIME__;
        history.push_back(calc);
        
        cout << "Result: " << result << endl;
        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}