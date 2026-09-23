#pragma once
#include <string>

class Product {
private:
    int id;
    std::string name;
    int price;
    int stock;

public:
    Product(int id = 0, std::string name = "", int price = 0, int stock = 0)
        : id(id), name(name), price(price), stock(stock) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getPrice() const { return price; }
    int getStock() const { return stock; }
    
    void setStock(int newStock) { stock = newStock; }

    std::string display() const {
        return std::to_string(id) + " -- " + name + "  Rs." + std::to_string(price) + "   Stock - " + std::to_string(stock) + "\n";
    }
};
