#include "../include/Calc-header.h"

int main() {
    vector<calculation> history;
    checkDatafile(history);
    double a, b;
    char operation;
    bool run = true;
    do {
        cout << "Enter operation ((a)dd, (s)ub, (m)ulti, (d)iv, (q)uit, (h)Displayhistory, (w)ritehistory, (l)oadhistory): ";
        cin >> operation;
        if (cin.fail() || (operation != 'a' && operation != 's' && operation != 'm' && operation != 'd' && operation != 'q' && operation != 'h' && operation != 'w' && operation != 'l')) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid operation." << endl;
            continue;
        }
        operation = tolower(operation);
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
        cout << "Enter first number: "; cin >> a;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }
        cout << "Enter second number: "; cin >> b;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }
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
        cout << endl << "Do you want to continue? (y/n): ";
        char cont; cin >> cont;
        if (tolower(cont) == 'n') {
            run = false;
            save(history);
            cout << "History saved. Goodbye!" << endl;
            return 0;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (run);
    return 0;
}