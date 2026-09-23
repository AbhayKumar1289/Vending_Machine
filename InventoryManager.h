#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Product.h"

class InventoryManager {
private:
    std::vector<Product> products;
    std::string dbFile = "input.txt";

public:
    InventoryManager() {
        loadInventory();
    }

    void loadInventory() {
        products.clear();
        std::ifstream infile(dbFile);
        if (!infile) {
            std::cout << "Inventory file not found. Starting fresh.\n";
            return;
        }
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string temp;
            int id, price, stock;
            std::string name;
            
            std::getline(ss, temp, ' '); id = std::stoi(temp);
            std::getline(ss, name, ' ');
            std::getline(ss, temp, ' '); price = std::stoi(temp);
            std::getline(ss, temp, ' '); stock = std::stoi(temp);
            
            products.emplace_back(id, name, price, stock);
        }
        infile.close();
    }

    void saveInventory() {
        std::ofstream outfile(dbFile);
        for (const auto& p : products) {
            outfile << p.getId() << " " << p.getName() << " " << p.getPrice() << " " << p.getStock() << "\n";
        }
        outfile.close();
    }

    std::string displayAllProducts() const {
        std::string s;
        for (const auto& p : products) {
            if (p.getStock() > 0) {
                s += p.display();
            }
        }
        return s;
    }

    std::string displayAllProductsOwner() const {
        std::string s;
        for (const auto& p : products) {
            s += p.display();
        }
        return s;
    }

    Product* getProductById(int id) {
        if (id > 0 && id <= products.size()) {
            return &products[id - 1];
        }
        return nullptr;
    }

    void addProduct(const std::string& name, int price, int stock) {
        int newId = products.size() + 1;
        products.emplace_back(newId, name, price, stock);
        saveInventory();
    }

    void updateStock(int id, int addedStock) {
        Product* p = getProductById(id);
        if (p != nullptr) {
            p->setStock(p->getStock() + addedStock);
            saveInventory();
        } else {
            std::cout << "Product ID not found!\n";
        }
    }
};
