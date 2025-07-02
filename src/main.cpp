#include "../include/Calc-header.h"

int main() {
    // Vector to store calculation history
    vector<calculation> history;
    // Load or create the data file and history
    checkDatafile(history);
    double a, b; // Operands for menu-driven mode
    char operation; // Operation character for menu-driven mode
    bool run = true; // Controls the main loop
    int mode = 0; // Input mode: 1 = menu, 2 = expression

    // --- Input mode selection with error handling ---
    while (true) {
        cout << "Select input mode: 1) Menu-driven  2) Expression input\nEnter 1 or 2: ";
        if (!(cin >> mode)) { // Check for non-numeric input
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1 or 2." << endl;
            continue;
        }
        if (mode != 1 && mode != 2) { // Only allow 1 or 2
            cout << "Invalid choice. Please enter 1 or 2." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        break;
    }

    // --- Main calculator loop ---
    do {
        if (mode == 2) {
            // --- Expression input mode with error handling ---
            cout << "Enter a math expression (or type 'q' to quit, 'h' for history, 'w' to save, 'l' to load): ";
            string expr;
            getline(cin, expr);
            if (expr.empty()) { // Prevent empty input
                cout << "Input cannot be empty. Please enter a valid expression or command." << endl;
                continue;
            }
            // Handle special commands
            if (expr == "q") {
                cout << "Exiting calculator. Saving history. Goodbye!" << endl;
                save(history);
                break;
            } else if (expr == "w") { save(history); continue; }
            else if (expr == "l") { history.clear(); load(history); continue; }
            else if (expr == "h") {
                cout << "History of calculations:" << endl;
                for (const auto& calc : history)
                    cout << "Operation: " << calc.operation << ", Expression: " << calc.expression << ", Result: " << calc.result << ", Timestamp: " << calc.timestamp << endl;
                continue;
            }
            // Try to parse and calculate the expression
            if (!parseAndCalculate(expr, history)) {
                cout << "Invalid expression or calculation error." << endl;
            }
        } else {
            // --- Menu-driven mode with error handling ---
            cout << "Enter operation ((a)dd, (s)ub, (m)ulti, (d)iv, (q)uit, (h)Displayhistory, (w)ritehistory, (l)oadhistory): ";
            cin >> operation;
            if (cin.fail()) { // Check for invalid input
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid operation." << endl;
                continue;
            }
            if (operation != 'a' && operation != 's' && operation != 'm' && operation != 'd' && operation != 'q' && operation != 'h' && operation != 'w' && operation != 'l') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid operation. Please enter a valid option." << endl;
                continue;
            }
            operation = tolower(operation);
            // Handle special commands
            if (operation == 'q') {
                cout << "Exiting calculator. Saving history. Goodbye!" << endl;
                save(history);
                break;
            }
            if (operation == 'w') { save(history); continue; }
            if (operation == 'l') { history.clear(); load(history); continue; }
            if (operation == 'h') {
                cout << "History of calculations:" << endl;
                for (const auto& calc : history)
                    cout << "Operation: " << calc.operation << ", Expression: " << calc.expression << ", Result: " << calc.result << ", Timestamp: " << calc.timestamp << endl;
                continue;
            }
            // Get first number
            cout << "Enter first number: "; cin >> a;
            if (cin.fail()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }
            // Get second number
            cout << "Enter second number: "; cin >> b;
            if (cin.fail()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }
            // Perform the selected operation
            if (operation == 'a') {
                cout << "Sum: " << add(a, b) << endl;
                history.push_back({"add", to_string(a) + " + " + to_string(b), to_string(add(a, b)), __DATE__ " " __TIME__});
            } else if (operation == 's') {
                cout << "Difference: " << sub(a, b) << endl;
                history.push_back({"subtract", to_string(a) + " - " + to_string(b), to_string(sub(a, b)), __DATE__ " " __TIME__});
            } else if (operation == 'm') {
                cout << "Product: " << multi(a, b) << endl;
                history.push_back({"multiply", to_string(a) + " * " + to_string(b), to_string(multi(a, b)), __DATE__ " " __TIME__});
            } else if (operation == 'd') {
                cout << div_print(a, b) << endl;
                history.push_back({"divide", to_string(a) + " / " + to_string(b), div_print(a, b), __DATE__ " " __TIME__});
            } else {
                cout << "Invalid operation!" << endl;
                continue;
            }
        }
        // Ask user if they want to continue
        cout << endl << "Do you want to continue? (y/n): ";
        char cont; cin >> cont; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(cont) == 'n') {
            run = false;
            save(history);
            cout << "History saved. Goodbye!" << endl;
            return 0;
        }
    } while (run);
    return 0;
}