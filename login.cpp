#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>      // For system()
#include <sys/stat.h>   // For mkdir()
#include <functional>   // For std::hash

using namespace std;

// Check if file exists
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Hash password
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Register new user
void registerUser() {
    string username, password;
    cout << "\n--- Registration ---\n";
    cout << "Enter username: ";
    cin >> username;

    string filepath = "users/" + username + ".txt";

    if (fileExists(filepath)) {
        cout << "Username already exists. Please choose another.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Hash the password
    string hashedPass = hashPassword(password);

    // Create users folder (platform-specific)
    #ifdef _WIN32
        system("mkdir users");
    #else
        mkdir("users", 0777);
    #endif

    // Save user data
    ofstream userFile(filepath);
    userFile << hashedPass;
    userFile.close();

    cout << "Registration successful!\n";
}

// Login function
void loginUser() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    cin >> username;

    string filepath = "users/" + username + ".txt";

    if (!fileExists(filepath)) {
        cout << "Username does not exist.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    string hashedInput = hashPassword(password);

    ifstream userFile(filepath);
    string storedHash;
    getline(userFile, storedHash);
    userFile.close();

    if (hashedInput == storedHash) {
        cout << "Login successful. Welcome, " << username << "!\n";
    } else {
        cout << "Invalid password.\n";
    }
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
