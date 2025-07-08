#include "../include/Calc-header.h"


// Main entry point for the Advanced Calculator application
int main() {
    // Create a CalculationHistory object to manage calculation history
    CalculationHistory history;
    // Check if the data file and directory exist, create/load as needed
    history.checkDatafile();
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
            // Handle special commands for expression mode
            if (expr == "q") {
                cout << "Exiting calculator. Saving history. Goodbye!" << endl;
                history.save();
                break;
            } else if (expr == "w") {
                cout << "Saving history..." << endl;
                if (history.empty()) {
                    cout << "No history to save." << endl;
                } else {
                    history.save();
                    cout << "History saved successfully." << endl;
                }
                continue;
            }
            else if (expr == "l") {
                // Load history from file, with confirmation if history already exists
                cout << "Loading history..." << endl;
                if (history.empty()) {
                    history.load();
                    cout << "History loaded successfully." << endl;
                }
                else {
                    // Ask user if they want to overwrite current history
                    cout << "Do you want to overwrite the current history? (y/n): ";
                    char choice;
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (tolower(choice) == 'y') {
                        history.clear();
                        history.load();
                        cout << "History loaded successfully." << endl;
                    } else {
                        cout << "Current history retained." << endl;
                        cout << "Do you want still want to load history? (y/n): ";
                        char loadChoice;
                        cin >> loadChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (tolower(loadChoice) == 'y') {
                            history.load();
                            cout << "History loaded successfully." << endl;
                        } else {
                            cout << "Current history retained." << endl;
                        }
                    }
                }
                continue;
            }
            else if (expr == "h") {
                // Display calculation history
                cout << "Displaying calculation history:" << endl;
                if (history.empty()) {
                    cout << "No history available." << endl;
                } else {
                    cout << "History of calculations:" << endl;
                    history.display();
                }
                continue;
            }
            // Try to parse and calculate the expression
            if (!Calculator::parseAndCalculate(expr, history)) {
                cout << "Invalid expression or calculation error." << endl;
            }
        } else {
            // --- Menu-driven mode with error handling ---
            cout << "Enter operation ((a)dd, (s)ub, (m)ulti, (d)iv, (p)owering(exponentiation), (q)uit, (h)Displayhistory, (w)ritehistory, (l)oadhistory): ";
            cin >> operation;
            if (cin.fail()) { // Check for invalid input
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid operation." << endl;
                continue;
            }
            // Only allow valid operation characters
            if (operation != 'a' && operation != 's' && operation != 'm' && operation != 'd' && operation != 'q' && operation != 'h' && operation != 'w' && operation != 'l' && operation != 'p') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid operation. Please enter a valid option." << endl;
                continue;
            }
            operation = tolower(operation);
            // Handle special commands for menu mode
            if (operation == 'q') {
                cout << "Exiting calculator. Saving history. Goodbye!" << endl;
                history.save();
                break;
            }
            if (operation == 'w') { history.save(); continue; }
            if (operation == 'l') { history.clear(); history.load(); continue; }
            if (operation == 'h') { history.display(); continue; }
            // Get first number from user
            cout << "Enter first number: "; cin >> a;
            if (cin.fail()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }
            // Get second number from user
            cout << "Enter second number: "; cin >> b;
            if (cin.fail()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }
            // Perform the selected operation and add to history
            if (operation == 'a') {
                cout << "Sum: " << Calculator::add(a, b) << endl;
                history.add(Calculation("add", to_string(a) + " + " + to_string(b), to_string(Calculator::add(a, b)), __DATE__ " " __TIME__));
            } else if (operation == 's') {
                cout << "Difference: " << Calculator::sub(a, b) << endl;
                history.add(Calculation("subtract", to_string(a) + " - " + to_string(b), to_string(Calculator::sub(a, b)), __DATE__ " " __TIME__));
            } else if (operation == 'm') {
                cout << "Product: " << Calculator::multi(a, b) << endl;
                history.add(Calculation("multiply", to_string(a) + " * " + to_string(b), to_string(Calculator::multi(a, b)), __DATE__ " " __TIME__));
            } else if (operation == 'd') {
                cout << Calculator::div_print(a, b) << endl;
                history.add(Calculation("divide", to_string(a) + " / " + to_string(b), Calculator::div_print(a, b), __DATE__ " " __TIME__));
            } else if (operation == 'p') {
                cout << "Power: " << Calculator::pow(a, b) << endl;
                history.add(Calculation("power", to_string(a) + " ^ " + to_string(b), to_string(Calculator::pow(a, b)), __DATE__ " " __TIME__));
            } else {
                cout << "Invalid operation!" << endl;
                continue;
            }
        }
        // Ask user if they want to continue or exit
        cout << endl << "Do you want to continue? (y/n): ";
        char cont; cin >> cont; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(cont) == 'n') {
            run = false;
            history.save();
            cout << "History saved. Goodbye!" << endl;
            return 0;
        }
    } while (run);
    return 0;
}
