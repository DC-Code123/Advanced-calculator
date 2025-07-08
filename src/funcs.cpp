#include "../include/Calc-header.h"


// Implementation of CalculationHistory methods

// Checks if the data directory and file exist, creates them if not, and loads history from file
void CalculationHistory::checkDatafile() {
    namespace fs = filesystem;
    string dir = "data", filename = dir + "/history.txt";
    try {
        // Check if data directory exists, create if not
        if (!fs::exists(dir)) {
            if (!fs::create_directory(dir)) {
                cout << "Error: Could not create data directory!" << endl;
                return;
            }
        }
        // Check if history file exists, create if not, otherwise load
        if (!fs::exists(filename)) {
            cout << "Data file not found. Creating new data file..." << endl;
            createDatafile();
        } else {
            cout << "Data file found." << endl;
            load();
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Filesystem error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "General error: " << e.what() << endl;
    }
}

// Creates a new data file with a header for calculation history
void CalculationHistory::createDatafile() {
    ofstream file("data/history.txt");
    if (file.is_open()) {
        file << "Operation,Expression,Result,Timestamp\n";
        file.close();
        cout << "New data file created in /data." << endl;
    } else {
        cerr << "Failed to create data file in /data. Please check permissions." << endl;
    }
}

// Saves the calculation history to the data file, replacing any existing content
void CalculationHistory::save() {
    ofstream file("data/history.txt");
    if (!file.is_open()) {
        cerr << "Failed to save history to file in /data. Please check permissions." << endl;
        return;
    }
    file << "Operation,Expression,Result,Timestamp\n";
    for (const auto& calc : history) {
        // Replace commas in expression and result to avoid CSV issues
        string expr = calc.expression; replace(expr.begin(), expr.end(), ',', ';');
        string res = calc.result; replace(res.begin(), res.end(), ',', ';');
        file << calc.operation << "," << expr << "," << res << "," << calc.timestamp << "\n";
        if (!file) { cerr << "Error writing to file. Data may be incomplete." << endl; break; }
    }
    file.close();
    cout << "History saved to file in /data." << endl;
}

// Loads the calculation history from the data file, handling malformed lines
void CalculationHistory::load() {
    ifstream file("data/history.txt");
    if (!file.is_open()) {
        cerr << "Failed to open data file in /data for loading." << endl;
        return;
    }
    string line; getline(file, line); // Skip header
    int lineNum = 1;
    while (getline(file, line)) {
        lineNum++;
        stringstream ss(line);
        string operation, expression, result, timestamp;
        // Parse CSV line into calculation fields
        if (!getline(ss, operation, ',') || !getline(ss, expression, ',') || !getline(ss, result, ',') || !getline(ss, timestamp, ',')) {
            cerr << "Warning: Malformed line in history file at line " << lineNum << ". Skipping." << endl;
            continue;
        }
        Calculation calc(operation, expression, result, timestamp);
        history.push_back(calc);
    }
    if (file.bad()) cerr << "Error reading from file. Data may be incomplete." << endl;
    file.close();
    cout << "History loaded from file in /data." << endl;
}

// Adds a new calculation to the history
void CalculationHistory::add(const Calculation& calc) {
    history.push_back(calc);
}

// Clears the calculation history in memory
void CalculationHistory::clear() {
    history.clear();
}

// Returns true if the calculation history is empty
bool CalculationHistory::empty() const {
    return history.empty();
}

// Displays the calculation history to the console
void CalculationHistory::display() const {
    cout << "History of calculations:" << endl;
    for (const auto& calc : history) {
        cout << "Operation: " << calc.operation << ", Expression: " << calc.expression << ", Result: " << calc.result << ", Timestamp: " << calc.timestamp << endl;
    }
}

// Returns a reference to the internal history vector
vector<Calculation>& CalculationHistory::getHistory() {
    return history;
}

// --- Math Operations ---
// --- Math Operations with Advanced Validation ---
// --- Math Operations with Advanced Validation and Detailed Comments ---

// Implementation of Calculator methods

// Adds two numbers and checks for overflow/underflow
double Calculator::add(double x, double y) {
    double result = x + y;
    // If both numbers are positive but result is negative, or both negative and result is positive, overflow/underflow happened
    if ((x > 0 && y > 0 && result < 0) || (x < 0 && y < 0 && result > 0)) {
        cerr << "Warning: Addition overflow/underflow detected." << endl;
    }
    return result;
}

// Subtracts y from x and checks for overflow/underflow
double Calculator::sub(double x, double y) {
    double result = x - y;
    // If x is positive and y is negative but result is negative, or x is negative and y is positive but result is positive, overflow/underflow happened
    if ((x > 0 && y < 0 && result < 0) || (x < 0 && y > 0 && result > 0)) {
        cerr << "Warning: Subtraction overflow/underflow detected." << endl;
    }
    return result;
}

// Divides x by y, checks for division by zero and non-finite numbers
double Calculator::div(double x, double y) {
    if (y == 0) {
        cerr << "Error: Division by zero" << endl;
        return NAN;
    }
    if (!isfinite(x) || !isfinite(y)) {
        cerr << "Error: Non-finite number in division." << endl;
        return NAN;
    }
    return x / y;
}

// Multiplies two numbers and checks for overflow/underflow
double Calculator::multi(double x, double y) {
    double result = x * y;
    // If x is not zero and dividing result by x doesn't give y, overflow/underflow happened
    if (x != 0 && result / x != y) {
        cerr << "Warning: Multiplication overflow/underflow detected." << endl;
    }
    return result;
}

// Returns the remainder of x divided by y, checks for modulus by zero and non-finite numbers
double Calculator::mod(double x, double y) {
    if (y == 0) {
        cerr << "Error: Modulus by zero" << endl;
        return NAN;
    }
    if (!isfinite(x) || !isfinite(y)) {
        cerr << "Error: Non-finite number in modulus." << endl;
        return NAN;
    }
    return fmod(x, y);
}

// Returns a string showing the quotient and remainder, with error message for division by zero
string Calculator::div_print(double x, double y) {
    if (y == 0) return "Error: Division by zero";
    double quotient = div(x, y), remainder = mod(x, y);
    return to_string(quotient) + " R " + to_string(remainder);
}

// Raises base to the power of exponent, with error checking
double Calculator::pow(double base, double exponent) {
    if (base == 0 && exponent <= 0) {
        cerr << "Error: Invalid operation: 0 raised to a non-positive power." << endl;
        return NAN;
    }
    if (!isfinite(base) || !isfinite(exponent)) {
        cerr << "Error: Non-finite number in power operation." << endl;
        return NAN;
    }
    return std::pow(base, exponent);
}

// --- Utility Functions ---

// Checks if a string is a valid number (including scientific notation, not too long, not empty)
bool Calculator::isNumber(const string& s) {
    if (s.empty() || s.length() > 100) return false; // Reject empty or too long input
    try {
        size_t idx;
        double val = stod(s, &idx); // Try to convert to double
        if (idx != s.size()) return false; // Extra characters after number
        if (!isfinite(val)) return false; // Not a finite number (inf or NaN)
        return true;
    } catch (...) { return false; }
}

// Returns true if the token is a supported operator
bool Calculator::isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

// Returns the precedence of an operator (higher value = higher precedence)
int Calculator::getPrecedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    return 0;
}

// Tokenizes and validates a math expression string
// Splits the input into numbers, operators, and parentheses, and checks for invalid characters and unbalanced parentheses
vector<string> Calculator::tokenize(const string& expr) {
    vector<string> tokens; string current;
    int parenCount = 0;
    for (char c : expr) {
        if (isspace(c)) continue; // Ignore spaces
        if (isdigit(c) || c == '.') current += c; // Build up a number
        else if (c == '(') {
            parenCount++;
            if (!current.empty()) { tokens.push_back(current); current.clear(); }
            tokens.push_back("(");
        } else if (c == ')') {
            parenCount--;
            if (parenCount < 0) cerr << "Warning: Unmatched closing parenthesis." << endl;
            if (!current.empty()) { tokens.push_back(current); current.clear(); }
            tokens.push_back(")");
        } else if (isOperator(string(1, c))) {
            if (!current.empty()) { tokens.push_back(current); current.clear(); }
            // Handle negative numbers (unary minus)
            if (c == '-' && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()))) current += c;
            else tokens.push_back(string(1, c));
        } else {
            // Any other character is invalid
            cerr << "Warning: Invalid character '" << c << "' in expression." << endl;
        }
    }
    if (!current.empty()) tokens.push_back(current); // Add last number
    if (parenCount != 0) cerr << "Warning: Unbalanced parentheses in expression." << endl;
    return tokens;
}

// Converts infix tokens to postfix (Reverse Polish Notation) using the shunting yard algorithm
vector<string> Calculator::infixToPostfix(const vector<string>& tokens) {
    vector<string> postfix; stack<string> opStack;
    for (const string& token : tokens) {
        if (isNumber(token)) postfix.push_back(token);
        else if (token == "(") opStack.push(token);
        else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                postfix.push_back(opStack.top()); opStack.pop();
            }
            opStack.pop();
        } else if (isOperator(token)) {
            while (!opStack.empty() && getPrecedence(opStack.top()) >= getPrecedence(token)) {
                postfix.push_back(opStack.top()); opStack.pop();
            }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) { postfix.push_back(opStack.top()); opStack.pop(); }
    return postfix;
}

// Evaluates a postfix expression with advanced validation
// Checks for enough operands, non-finite numbers, and result validity
double Calculator::evaluatePostfix(const vector<string>& postfix) {
    stack<double> valStack;
    for (const string& token : postfix) {
        if (isNumber(token)) valStack.push(stod(token)); // Push numbers onto the stack
        else if (isOperator(token)) {
            if (valStack.size() < 2) throw runtime_error("Invalid expression: not enough operands");
            double b = valStack.top(); valStack.pop();
            double a = valStack.top(); valStack.pop();
            // Check that operands are finite
            if (!isfinite(a) || !isfinite(b)) throw runtime_error("Non-finite operand in expression");
            double result;
            // Perform the operation
            if (token == "+") result = add(a, b);
            else if (token == "-") result = sub(a, b);
            else if (token == "*") result = multi(a, b);
            else if (token == "/") result = div(a, b);
            else if (token == "%") result = mod(a, b);
            // Check that result is finite
            if (!isfinite(result)) throw runtime_error("Result is not a finite number");
            valStack.push(result);
        }
    }
    // There should be exactly one result on the stack
    if (valStack.size() != 1) throw runtime_error("Invalid expression");
    return valStack.top();
}

// Evaluates a math expression string by tokenizing, converting to postfix, and evaluating
double Calculator::evaluateExpression(const string& expr) {
    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

// Parses a string input, evaluates it, and adds the result to history if valid
bool Calculator::parseAndCalculate(const string& input, CalculationHistory& history) {
    try {
        if (input.empty()) return false;
        double result = evaluateExpression(input);
        if (isnan(result)) { cerr << "Calculation error occurred" << endl; return false; }
        history.add(Calculation("expression", input, to_string(result), __DATE__ " " __TIME__));
        cout << "Result: " << result << endl;
        return true;
    } catch (const exception& e) { cerr << "Error: " << e.what() << endl; return false; }
}
