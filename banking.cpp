#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string note;

    Transaction(string t, double amt, string n = "") {
        type = t;
        amount = amt;
        note = n;
    }
};

class Account {
private:
    double balance;
    vector<Transaction> transactions;

public:
    Account() {
        balance = 0.0;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposited ₹" << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            transactions.emplace_back("Withdrawal", amount);
            cout << "Withdrawn ₹" << amount << " successfully.\n";
        }
    }

    bool transferTo(Account &receiver, double amount) {
        if (amount > balance) {
            cout << "Transfer failed: Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        receiver.receiveTransfer(amount);
        transactions.emplace_back("Transfer Sent", amount);
        cout << "Transferred ₹" << amount << " successfully.\n";
        return true;
    }

    void receiveTransfer(double amount) {
        balance += amount;
        transactions.emplace_back("Transfer Received", amount);
    }

    void printTransactionHistory() {
        cout << "\n--- Transaction History ---\n";
        for (auto &t : transactions) {
            cout << setw(18) << left << t.type << " ₹" << t.amount;
            if (!t.note.empty()) cout << " (" << t.note << ")";
            cout << endl;
        }
    }

    double getBalance() {
        return balance;
    }
};

class Customer {
public:
    string name;
    int id;
    Account account;

    Customer(string n, int i) {
        name = n;
        id = i;
    }

    void displayInfo() {
        cout << "\nCustomer Name: " << name << "\nCustomer ID: " << id
             << "\nAccount Balance: ₹" << account.getBalance() << endl;
    }
};

// Main menu
int main() {
    Customer customer1("Arya", 101);
    Customer customer2("Riya", 102);

    int choice;
    double amt;

    do {
        cout << "\n========== BANKING MENU ==========\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Fund Transfer (to Riya)\n";
        cout << "4. View Transaction History\n";
        cout << "5. Display Account Info\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: ₹";
                cin >> amt;
                customer1.account.deposit(amt);
                break;

            case 2:
                cout << "Enter amount to withdraw: ₹";
                cin >> amt;
                customer1.account.withdraw(amt);
                break;

            case 3:
                cout << "Enter amount to transfer to Riya: ₹";
                cin >> amt;
                customer1.account.transferTo(customer2.account, amt);
                break;

            case 4:
                customer1.account.printTransactionHistory();
                break;

            case 5:
                customer1.displayInfo();
                break;

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
