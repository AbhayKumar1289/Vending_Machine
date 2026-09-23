#pragma once
#include <memory>
#include "State.h"
#include "InventoryManager.h"
#include "CoinManager.h"

class VendingMachine {
private:
    std::unique_ptr<State> currentState;
    InventoryManager inventory;
    CoinManager coinManager;

public:
    VendingMachine(std::unique_ptr<State> initialState) 
        : currentState(std::move(initialState)) {}

    void changeState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
    }

    InventoryManager& getInventory() { return inventory; }
    CoinManager& getCoinManager() { return coinManager; }

    void insertMoney() {
        if (currentState) currentState->insertMoney(this);
    }

    void selectProduct() {
        if (currentState) currentState->selectProduct(this);
    }

    void dispense() {
        if (currentState) currentState->dispense(this);
    }

    void enterOwnerMode() {
        if (currentState) currentState->enterOwnerMode(this);
    }
};
