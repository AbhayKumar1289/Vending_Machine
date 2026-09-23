#include <cassert>
#include <iostream>
#include "../CoinManager.h"
#include "../Product.h"
#include "../InventoryManager.h"

void test_coin_manager() {
    CoinManager cm;
    
    // Test exact change algorithm
    cm.insertCoin(20);
    cm.insertCoin(10);
    assert(cm.getBalance() == 30);
    
    // Dispense product costing 25. Should give 5 change.
    bool success = cm.dispenseChangeAndFinalize(25);
    assert(success == true);
    assert(cm.getBalance() == 0); // Balance clears
    
    // Test invalid denomination
    cm.insertCoin(3);
    assert(cm.getBalance() == 0);

    // Test failing transaction (insufficient funds)
    cm.insertCoin(10);
    success = cm.dispenseChangeAndFinalize(15);
    assert(success == false);
    assert(cm.getBalance() == 10); // Balance stays so user can add more or refund
    
    std::cout << "CoinManager tests passed!\n";
}

void test_product() {
    Product p(1, "TestSoda", 20, 5);
    assert(p.getId() == 1);
    assert(p.getName() == "TestSoda");
    assert(p.getPrice() == 20);
    assert(p.getStock() == 5);
    
    p.setStock(4);
    assert(p.getStock() == 4);
    
    std::cout << "Product tests passed!\n";
}

int main() {
    std::cout << "Running automated unit tests...\n";
    test_coin_manager();
    test_product();
    std::cout << "All tests passed successfully.\n";
    return 0;
}
