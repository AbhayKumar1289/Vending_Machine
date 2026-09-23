#pragma once
#include <iostream>
#include <memory>
#include "State.h"
#include "VendingMachine.h"
#include "Utils.h"

class HasMoneyState;
class OwnerModeState;

class IdleState : public State {
public:
    void insertMoney(VendingMachine* machine) override;
    void selectProduct(VendingMachine* machine) override {
        std::cout << "Please insert money first.\n";
    }
    void dispense(VendingMachine* machine) override {
        std::cout << "No product selected.\n";
    }
    void enterOwnerMode(VendingMachine* machine) override;
};

class HasMoneyState : public State {
public:
    void insertMoney(VendingMachine* machine) override {
        int amount = Utils::getIntInput("Enter amount to insert (Rs.): ");
        if (amount > 0) {
            machine->getCoinManager().addBalance(amount);
            std::cout << "Total Balance: Rs. " << machine->getCoinManager().getBalance() << "\n";
        }
    }
    
    void selectProduct(VendingMachine* machine) override {
        std::cout << "\nAvailable Products:\n" << machine->getInventory().displayAllProducts();
        int productId = Utils::getIntInput("Enter Product ID to purchase (or 0 to cancel): ");
        
        if (productId == 0) {
            machine->getCoinManager().refundBalance();
            machine->changeState(std::make_unique<IdleState>());
            return;
        }

        Product* p = machine->getInventory().getProductById(productId);
        if (p == nullptr || p->getStock() <= 0) {
            std::cout << "Invalid product or out of stock.\n";
            return;
        }

        if (machine->getCoinManager().getBalance() >= p->getPrice()) {
            machine->getCoinManager().deductBalance(p->getPrice());
            machine->getCoinManager().recordProfit(p->getPrice());
            machine->getInventory().updateStock(productId, -1);
            
            std::cout << "\n>>> Dispensing " << p->getName() << " <<<\n";
            machine->getCoinManager().refundBalance();
            machine->changeState(std::make_unique<IdleState>());
        } else {
            std::cout << "Insufficient balance! Product costs Rs. " << p->getPrice() << "\n";
        }
    }
    
    void dispense(VendingMachine* machine) override {
        std::cout << "Please select a product first.\n";
    }

    void enterOwnerMode(VendingMachine* machine) override {
        std::cout << "Cannot enter owner mode while a transaction is active. Refunding money...\n";
        machine->getCoinManager().refundBalance();
        machine->changeState(std::make_unique<IdleState>());
    }
};

class OwnerModeState : public State {
public:
    void insertMoney(VendingMachine* machine) override {
        std::cout << "In owner mode. Cannot insert money.\n";
    }
    void selectProduct(VendingMachine* machine) override {
        std::cout << "In owner mode. Cannot purchase products.\n";
    }
    void dispense(VendingMachine* machine) override {
        std::cout << "In owner mode.\n";
    }
    void enterOwnerMode(VendingMachine* machine) override {
        while (true) {
            std::cout << "\n--- Owner Menu ---\n";
            std::cout << "1. Add New Product\n";
            std::cout << "2. Restock Product\n";
            std::cout << "3. View Profits\n";
            std::cout << "4. View All Products (Including Out of Stock)\n";
            std::cout << "5. Exit Owner Mode\n";
            int choice = Utils::getIntInput("Choice: ");

            if (choice == 1) {
                std::string name = Utils::getStringInput("Enter product name: ");
                int price = Utils::getIntInput("Enter price: ");
                int stock = Utils::getIntInput("Enter stock quantity: ");
                machine->getInventory().addProduct(name, price, stock);
                std::cout << "Product added successfully.\n";
            } else if (choice == 2) {
                std::cout << machine->getInventory().displayAllProductsOwner();
                int id = Utils::getIntInput("Enter Product ID to restock: ");
                int amount = Utils::getIntInput("Enter amount to add: ");
                machine->getInventory().updateStock(id, amount);
                std::cout << "Stock updated.\n";
            } else if (choice == 3) {
                machine->getCoinManager().printProfit();
            } else if (choice == 4) {
                std::cout << "\n" << machine->getInventory().displayAllProductsOwner();
            } else if (choice == 5) {
                std::cout << "Exiting Owner Mode...\n";
                machine->changeState(std::make_unique<IdleState>());
                break;
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
    }
};

// Now define the IdleState methods that needed the other classes defined first
inline void IdleState::insertMoney(VendingMachine* machine) {
    int amount = Utils::getIntInput("Enter amount to insert (Rs.): ");
    if (amount > 0) {
        machine->getCoinManager().addBalance(amount);
        std::cout << "Balance: Rs. " << machine->getCoinManager().getBalance() << "\n";
        machine->changeState(std::make_unique<HasMoneyState>());
    }
}

inline void IdleState::enterOwnerMode(VendingMachine* machine) {
    std::string pass = Utils::getStringInput("Enter Owner Password: ");
    if (pass == "vending123") {
        std::cout << "Authentication successful.\n";
        machine->changeState(std::make_unique<OwnerModeState>());
        machine->enterOwnerMode(); // immediately jump into the menu
    } else {
        std::cout << "Authentication failed.\n";
    }
}
