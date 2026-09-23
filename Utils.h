#pragma once
#include <iostream>
#include <limits>
#include <string>

class Utils {
public:
    static int getIntInput(const std::string& prompt) {
        int choice;
        while (true) {
            std::cout << prompt;
            if (std::cin >> choice) {
                return choice;
            } else {
                std::cout << "Invalid input. Please enter a valid number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    static std::string getStringInput(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::cin >> input;
        return input;
    }
};
