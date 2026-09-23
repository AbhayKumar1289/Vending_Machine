#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <numeric>

class CoinManager {
private:
    std::map<int, int, std::greater<int>> machineCoins; // Denomination -> Count, sorted descending
    std::map<int, int, std::greater<int>> insertedCoins; // Current transaction
    std::string profitFile = "profit.txt";

    // Helper to calculate total value of a coin map
    int calculateTotal(const std::map<int, int, std::greater<int>>& coins) const {
        int total = 0;
        for (const auto& pair : coins) {
            total += pair.first * pair.second;
        }
        return total;
    }

public:
    CoinManager() {
        // Initialize machine with some float (change)
        machineCoins[20] = 5;
        machineCoins[10] = 10;
        machineCoins[5]  = 20;
        machineCoins[2]  = 50;
        machineCoins[1]  = 50;
    }

    bool isValidDenomination(int amount) const {
        return amount == 1 || amount == 2 || amount == 5 || amount == 10 || amount == 20;
    }

    void insertCoin(int amount) {
        if (isValidDenomination(amount)) {
            insertedCoins[amount]++;
        } else {
            std::cout << "Invalid denomination! We only accept Rs. 1, 2, 5, 10, 20.\n";
        }
    }

    int getBalance() const {
        return calculateTotal(insertedCoins);
    }

    // Try to dispense change using greedy algorithm
    bool dispenseChangeAndFinalize(int productPrice) {
        int balance = getBalance();
        if (balance < productPrice) return false;

        int changeNeeded = balance - productPrice;
        std::map<int, int, std::greater<int>> changeToGive;
        
        // Temporarily merge inserted coins into machine inventory for change calculation
        for (const auto& pair : insertedCoins) {
            machineCoins[pair.first] += pair.second;
        }

        int remainingChange = changeNeeded;
        // Greedy Algorithm for exact change
        for (auto& pair : machineCoins) {
            int denom = pair.first;
            int count = pair.second;

            if (remainingChange >= denom && count > 0) {
                int coinsNeeded = remainingChange / denom;
                int coinsToTake = std::min(coinsNeeded, count);
                
                changeToGive[denom] = coinsToTake;
                remainingChange -= coinsToTake * denom;
            }
        }

        // If we can't make exact change, roll back
        if (remainingChange > 0) {
            std::cout << "Machine cannot provide exact change (needs Rs. " << changeNeeded << "). Rolling back transaction.\n";
            // Remove the inserted coins we temporarily added
            for (const auto& pair : insertedCoins) {
                machineCoins[pair.first] -= pair.second;
            }
            return false;
        }

        // Exact change is possible. Deduct the change from machine inventory
        for (const auto& pair : changeToGive) {
            machineCoins[pair.first] -= pair.second;
        }
        
        insertedCoins.clear();
        recordProfit(productPrice);

        if (changeNeeded > 0) {
            std::cout << "Returning change (Rs. " << changeNeeded << "): ";
            for (const auto& pair : changeToGive) {
                std::cout << pair.second << "x(Rs." << pair.first << ") ";
            }
            std::cout << "\n";
        }
        
        return true;
    }

    void refundBalance() {
        int balance = getBalance();
        if (balance > 0) {
            std::cout << "Refunding Rs. " << balance << "...\n";
            insertedCoins.clear();
        }
    }

    void recordProfit(int amount) {
        int existingProfit = 0;
        std::ifstream ifile(profitFile);
        std::string line;
        if (std::getline(ifile, line) && !line.empty()) {
            try {
                existingProfit = std::stoi(line);
            } catch (...) {} // Ignore malformed
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
