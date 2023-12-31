// Last Modified: 9/29/23
//completed

#include <iostream>
#include <fstream>
#include "HotelFunctions.h"

void Login::login() {
    std::string username, password;

    User login;
    int attempts = 0; // Initialize the login attempts counter

    while (attempts < 5) { // Allow a maximum of 5 login attempts
        std::cout << "\t\t-----LOG IN-----" << std::endl;
        std::cout << "Username: "<<std::endl;
        std::cin >> username;
        std::cout << "Password: " << std::endl;
        std::cin >> password;

        bool found = false;

        // File input to read the user's information
        std::ifstream ULogin("UserFiles.txt");
        while (ULogin >> login.uname >> login.pass >> login.lname >> login.fname >> login.phone >> login.email) {
            if (username == login.uname && password == login.pass) {
                std::cout << "\t\tSuccessfully Login" << std::endl;
                std::cout << "Name: " << login.lname << ", " << login.fname << std::endl;
                std::cout << "Phone Number: " << login.phone << std::endl;
                std::cout << "Email Address: " << login.email << std::endl;

                found = true;
                break;
            }
        }

        ULogin.close();

        if (found) {
            break; // Successful login, exit the loop
        } else {
            attempts++; // Increment the login attempts counter
            std::cout << "\t\tCheck again your username & password" << std::endl;
            std::cout << "\t\tRemaining attempts: " << 5 - attempts << std::endl;
        }
    }

    if (attempts == 5) {
        std::cout << "\t\tMaximum login attempts reached. Exiting program." << std::endl;
        exit(0); // Exit the program after 5 failed attempts
    }
}
