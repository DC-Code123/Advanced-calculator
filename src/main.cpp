#include "../include/Calc-header.h"


int main()
{
    // Vector to store the history of all calculations performed
    vector<calculation> history; // This keeps all our math answers

    double a, b; // Variables to store the two numbers entered by the user
    char operation; // Variable to store the operation selected by the user
    bool run = true; // Controls whether the calculator keeps running
    do {
        // Prompt the user to select an operation
        cout << "Enter operation ((a)dd, (s)ub, (m)ulti, (d)iv, (q)uit, (h)Displayhistory): ";
        cin >> operation;
        // If the user enters an invalid operation, handle the error and prompt again
        if (cin.fail() || (operation != 'a' && operation != 's' && operation != 'm' && operation != 'd' && operation != 'q' && operation != 'h')) 
        {
            cin.clear(); // Clean up if we made a mess
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Throw away the mess
            cout << "Invalid input. Please enter a valid operation." << endl;
            continue; // Start over
        }
        operation = tolower(operation); // Convert the operation to lowercase for consistency
        // Prompt the user to enter the first number
        cout << "Enter first number: ";
        cin >> a;
        // Prompt the user to enter the second number
        cout << "Enter second number: ";
        cin >> b;

        // If the user chooses to quit, exit the program
        if (operation == 'q')
        {
            cout << "Exiting calculator. Goodbye!" << endl;
            break;
        }
        // If the user selects addition
        if (operation == 'a')
        {
            cout << "Sum: " << add(a, b) << endl; // Display the result of addition
            calculation calc;
            calc.operation = "add"; // Store the operation type
            calc.expression = to_string(a) + " + " + to_string(b); // Store the expression
            calc.result = to_string(add(a, b)); // Store the result
            calc.timestamp = __DATE__ " " __TIME__; // Store the date and time
            history.push_back(calc); // Add this calculation to the history
        }
        // If the user selects subtraction
        else if (operation == 's')
        {
            cout << "Difference: " << sub(a, b) << endl; // Display the result of subtraction
            calculation calc;
            calc.operation = "subtract";
            calc.expression = to_string(a) + " - " + to_string(b);
            calc.result = to_string(sub(a, b));
            calc.timestamp = __DATE__ " " __TIME__;
            history.push_back(calc);
        }
        // If the user selects multiplication
        else if (operation == 'm')
        {
            cout << "Product: " << multi(a, b) << endl; // Display the result of multiplication
            calculation calc;
            calc.operation = "multiply";
            calc.expression = to_string(a) + " * " + to_string(b);
            calc.result = to_string(multi(a, b));
            calc.timestamp = __DATE__ " " __TIME__;
            history.push_back(calc);
        }
        // If the user selects division
        else if (operation == 'd')
        {
            cout << div_print(a, b) << endl; // Display the result of division
            calculation calc;
            calc.operation = "divide";
            calc.expression = to_string(a) + " / " + to_string(b);
            calc.result = div_print(a, b);
            calc.timestamp = __DATE__ " " __TIME__;
            history.push_back(calc);
        }
        // If the user wants to see the history of calculations
        else if (operation == 'h')
        {
            cout << "History of calculations:" << endl; // Display all previous calculations
            for (const auto& calc : history)
            {
                // Print each calculation's details
                cout << "Operation: " << calc.operation << ", Expression: " << calc.expression
                    << ", Result: " << calc.result << ", Timestamp: " << calc.timestamp << endl;
            }
        }
        // If the user enters an invalid operation (should not happen due to earlier check)
        else
        {
            cout << "Invalid operation!" << endl;
            continue; // Try again
        }
        cout << endl;
        // Ask the user if they want to perform another calculation
        cout << "Do you want to continue? (y/n): ";
        if (cin.get() == 'n')
        {
            run = false; // Exit the loop if the user says no
            return 0;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer for the next loop
        }
    } 
    while (run == true);
    return 0;
}