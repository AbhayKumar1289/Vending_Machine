#pragma once

class VendingMachine; // Forward declaration

class State {
public:
    virtual ~State() {}
    virtual void insertMoney(VendingMachine* machine) = 0;
    virtual void selectProduct(VendingMachine* machine) = 0;
    virtual void dispense(VendingMachine* machine) = 0;
    virtual void enterOwnerMode(VendingMachine* machine) = 0;
};
