#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

// - NegativeDepositException (for negative deposit attempts)
class NegativeDepositException : public runtime_error 
{
public:
    NegativeDepositException()
        : runtime_error("Invalid deposit. Can't deposit a negative amount!") {}
};
// - OverdrawException (for withdrawing more than the balance)
class OverdrawException : public runtime_error
{
public:
    OverdrawException() : runtime_error("Insufficient funds!") {}
};
// - InvalidAccountOperationException (for transactions on a closed account)
class InvalidAccountOperationException : public runtime_error
{
public: InvalidAccountOperationException()
    : runtime_error("The account is closed!") {}
};

class BankAccount {
private:
    string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        if (!isActive) {
            throw InvalidAccountOperationException();
        }
        if (amount < 0)
        {
            throw NegativeDepositException();
        }
        balance += amount;
    }

    // Withdraw method
    void withdraw(double amount) {
        if (!isActive)
        {
            throw InvalidAccountOperationException();
        }
        if (amount > balance)
        {
            throw OverdrawException();
        }
        balance -= amount;
    }

    // Method to get current balance
    double getBalance() const {
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        isActive = false;
    }
};

int main() {
    try {
        //Asks user to enter initial balance which will then be stored
        cout << "Enter initial balance: ";
        double initialBalance;
        cin >> initialBalance;

        auto account = make_unique<BankAccount>("123456", initialBalance); // Example initialization

        cout << "Bank Account Created: #" << "123456" << endl;
        
        //If initial balance is stored, greets user with a menu system that gives them the option, deposit, withdraw, check balance, close account, or exit
        while (true) {
            cout << "Welcome to the Bank Account Management System by Calvin Vo!" << endl;
            cout << "Depending on your input, you can choose to deposit, withdraw, check balance, close account, or exit." << endl;
            cout << "1. Deposit" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Check Balance" << endl;
            cout << "4. Close Account" << endl;
            cout << "5. Exit Program" << endl << endl;

            //User will enter input depending on what option they pick from the menu
            int input;
            cin >> input;
            switch (input) {
            //Deposit
            case 1:
                double deposit;
                cout << endl << "Enter deposit amount" << endl;
                cin >> deposit;
                account->deposit(deposit);
                break;
            case 2:
            // Withdraw money
                double withdraw;
                cout << "Enter your withdraw amount" << endl;
                cin >> withdraw;
                account->withdraw(withdraw);
                break;
            case 3:
            // Get Balance
                cout << account->getBalance() << endl;
                break;
            case 4:
            // Close the account of the user
                account->closeAccount();
                cout << "Your account has been closed succesfully!" << endl;
                break;
            case 5:
            // Ends the program
                cout << "Ending program" << endl;
                return 0;
            // If user enters any number that isn't 1-5
            default:
                cout << "Choice is invalid." << endl;

            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}