#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// Class to manage Bank Account logic
class BankAccount {
private:
    double balance;
    const int secretPIN = 1234; // Set default PIN
    const string balanceFile = "balance.txt";
    const string logFile = "transactions.log";

    // Helper to get current timestamp for bonus points
    string getTimestamp() {
        time_t now = time(0);
        char buf[80];
        struct tm tstruct;
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return string(buf);
    }

    // Record transactions in a log file
    void logTransaction(string type, double amount) {
        ofstream log(logFile, ios::app);
        if (log.is_open()) {
            log << "[" << getTimestamp() << "] " << type << ": $" 
                << fixed << setprecision(2) << amount 
                << " | New Balance: $" << balance << endl;
            log.close();
        }
    }

    // Save balance to file for persistence
    void saveBalanceToFile() {
        ofstream out(balanceFile);
        if (out.is_open()) {
            out << balance;
            out.close();
        }
    }

public:
    BankAccount() {
        // Load persistent balance from file or set default
        ifstream in(balanceFile);
        if (in.is_open()) {
            in >> balance;
            in.close();
        } else {
            balance = 500.0; // Default opening balance
        }
    }

    bool validatePIN(int input) {
        return input == secretPIN;
    }

    void checkBalance() {
        cout << "\n>>> Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << endl;
            logTransaction("DEPOSIT", amount);
            saveBalanceToFile();
            checkBalance();
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        const double minBalance = 100.0; // Validation requirement
        if (amount <= 0) {
            cout << "Invalid withdrawal amount." << endl;
        } else if (balance - amount < minBalance) {
            cout << "Transaction Failed: Minimum balance of $" << minBalance << " required." << endl;
        } else {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << endl;
            logTransaction("WITHDRAWAL", amount);
            saveBalanceToFile();
            checkBalance();
        }
    }
};

int main() {
    BankAccount userAccount;
    int enteredPIN;
    int attempts = 0;
    bool authenticated = false;

    cout << "--- Welcome to the ATM System ---" << endl;

    // PIN retry loop (Requirement 6)
    while (attempts < 3) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPIN;

        if (userAccount.validatePIN(enteredPIN)) {
            authenticated = true;
            break;
        } else {
            attempts++;
            cout << "Incorrect PIN. Attempts remaining: " << (3 - attempts) << endl;
        }
    }

    if (!authenticated) {
        cout << "\nSESSION BLOCKED: Too many incorrect attempts." << endl;
        return 0;
    }

    // ATM Menu System (Requirement 3 & 5)
    int choice;
    do {
        cout << "\n--- ATM MENU ---" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Option: ";
        cin >> choice;
        double amount;
        switch (choice) {
            case 1:
                userAccount.checkBalance();
                break;
            case 2:
                cout << "Enter deposit amount: $";
                cin >> amount;
                userAccount.deposit(amount);
                break;
            case 3:
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                userAccount.withdraw(amount);
                break;
            case 4:
                cout << "Thank you for using our ATM. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid selection. Please try again." << endl;
        }
    } 
    while (choice != 4);
    return 0;
}