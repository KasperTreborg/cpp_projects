#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;
hash<string> hasher;

int main() {


    fstream file ("savedDataTopSecret.txt", ios::in | ios::out);

    if (!file.is_open()) { 
        cerr << "Error opening the file!" << endl; 
        return 1; 
    }

    cout << "Do you have a user with us? [Y/n]: ";
    char response;
    cin >> response;

    if (response == 'n') {
        cout << "Please enter your desired username: ";
        string newUsername;
        cin.ignore();
        getline(cin, newUsername);

        string line;
        bool userExists = false;
        while (getline(file, line)) {
            string lineUsername = line.substr(0, line.find(" "));
            if (lineUsername == newUsername) {
                userExists = true;
                break;
            }
        }

        if (userExists) {
            cout << "Username already exists!" << endl;
            main();
        } else {
            cout << "Username is available!" << endl;
            cout << "Please enter your desired password: ";
            string newPassword;
            getline(cin, newPassword);

            size_t hashedPassword = hasher(newPassword);

            file.clear();
            file.seekp(0, ios::end);

            file << newUsername << " " << hashedPassword << "\n";
            cout << "User created successfully!";
        }
    }
    else if(response == 'Y') {
        cout << "Please enter your username: ";
        string newUsername;
        cin.ignore();
        getline(cin, newUsername);

        cout << "Please enter your password: ";
        string newPassword;
        getline(cin, newPassword);

        size_t hashedPassword = hasher(newPassword);

        string line;
        bool validLogin = false;
        while (getline(file, line)) {
            string lineUsername = line.substr(0, line.find(" "));
            string linePassword = line.substr(line.find(" ") + 1, line.length());
            if (lineUsername == newUsername && linePassword == to_string(hashedPassword)) {
                validLogin = true;
                break;
            }
            else if (lineUsername == newUsername && linePassword != to_string(hashedPassword)) {
                cout << "Invalid password!" << endl;
                main();
            }
        }

        if (validLogin) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Invalid login!" << endl;
            main();
        }
    }
    else {
        cout << "Invalid response!" << endl;
        main();
    }

    file.close();

    return 0;
}