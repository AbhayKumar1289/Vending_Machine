# Vending Machine Simulator

A modular, object-oriented C++ vending machine simulator that models real-world vending operations using the State Design Pattern.

## Architecture

This project was built to demonstrate core OOP principles, robust state-machine transitions, and encapsulation.

### State Design Pattern
The machine transitions smoothly between operational states to prevent illegal actions (e.g., trying to dispense a product without inserting money, or entering maintenance mode mid-transaction):
- **IdleState**: The machine is waiting for user interaction or owner authentication.
- **HasMoneyState**: The user has inserted coins. They can add more money, select a product, or request a refund.
- **OwnerModeState**: Authenticated maintenance state allowing the owner to restock inventory and view profits.

### Encapsulated Subsystems
- **InventoryManager**: Manages the loading, updating, and saving of product data (`input.txt`). Hides file I/O complexity from the main logic.
- **CoinManager**: Safely tracks current balances, handles exact change/refunds, and securely logs profits (`profit.txt`).
- **Robust Input Validation**: The utility layer prevents console crashes or infinite loops when users enter unexpected input (e.g., entering strings when integers are expected).

## How to Build and Run

You can compile the project using standard `g++`:

```bash
g++ main.cpp -o vending
./vending
```

## Features
- **Buyer Flow**: Insert money -> Check balance -> Select Product -> Dispense & Get Change.
- **Input Resilience**: Incorrect types are caught, buffers are cleared, and the user is gracefully prompted again.
- **Owner Maintenance**: Password-protected (default: `vending123`). Allows restocking, adding new items, and checking total revenue.
