#pragma once
#include <fstream>
#include <iostream>
#include <string>

class CoinManager {
private:
    int currentBalance = 0;
    std::string profitFile = "profit.txt";

public:
    void addBalance(int amount) {
        if (amount > 0) {
            currentBalance += amount;
        }
    }

    int getBalance() const {
        return currentBalance;
    }

    void deductBalance(int amount) {
        if (amount <= currentBalance) {
            currentBalance -= amount;
        }
    }

    void refundBalance() {
        if (currentBalance > 0) {
            std::cout << "Refunding Rs. " << currentBalance << "...\n";
            currentBalance = 0;
        }
    }

    void recordProfit(int amount) {
        int existingProfit = 0;
        std::ifstream ifile(profitFile);
        std::string line;
        if (std::getline(ifile, line) && !line.empty()) {
            existingProfit = std::stoi(line);
        }
        ifile.close();

        existingProfit += amount;
        
        std::ofstream ofile(profitFile);
        ofile << existingProfit << "\n";
        ofile.close();
    }

    void printProfit() const {
        std::ifstream ifile(profitFile);
        std::string x;
        if (std::getline(ifile, x) && !x.empty()) {
            std::cout << "Total profit is Rs. " << x << "\n";
        } else {
            std::cout << "Total profit is Rs. 0\n";
        }
    }
};
