#include <iostream>
#include <memory>
#include "VendingMachine.h"
#include "ConcreteStates.h"
#include "Utils.h"

int main() {
    std::cout << "==========================================\n";
    std::cout << "      VENDING MACHINE SIMULATOR 2.0       \n";
    std::cout << "==========================================\n";

    // Initialize the state machine with IdleState
    VendingMachine machine(std::make_unique<IdleState>());

    while (true) {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Insert Money\n";
        std::cout << "2. Select Product\n";
        std::cout << "3. Owner Maintenance Mode\n";
        std::cout << "4. Exit Simulator\n";
        
        int choice = Utils::getIntInput("Choose an option: ");

        switch (choice) {
            case 1:
                machine.insertMoney();
                break;
            case 2:
                machine.selectProduct();
                break;
            case 3:
                machine.enterOwnerMode();
                break;
            case 4:
                std::cout << "Shutting down simulator...\n";
                return 0;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
