# Vending Machine Simulator

A modular, object-oriented C++ vending machine simulator that models real-world vending operations using the State Design Pattern and robust engineering practices.

## Architecture

This project demonstrates core OOP principles, robust state-machine transitions, algorithm design, and automated testing.

### State Design Pattern
The machine transitions smoothly between operational states to prevent illegal actions (e.g., trying to dispense a product without inserting money, or entering maintenance mode mid-transaction):
- **IdleState**: The machine is waiting for user interaction or owner authentication.
- **HasMoneyState**: The user has inserted coins. They can add more money, select a product, or request a refund.
- **OwnerModeState**: Authenticated maintenance state allowing the owner to restock inventory and view profits.

### Denomination-Based Money Model (Greedy Algorithm)
Unlike simple balance trackers, the `CoinManager` tracks physical coin denominations (₹1, ₹2, ₹5, ₹10, ₹20) in the machine's internal inventory. When dispensing change, it utilizes a **Greedy Algorithm** to return the exact optimal combination of coins. If exact change is impossible due to inventory limits, the transaction rolls back gracefully.

### Encapsulated Subsystems & Hardened Persistence
- **InventoryManager**: Manages the loading, updating, and saving of product data (`input.txt`). It includes robust error handling to gracefully skip corrupted lines without crashing.
- **CoinManager**: Safely tracks current balances, computes exact change using the greedy algorithm, and securely logs profits (`profit.txt`).
- **Robust Input Validation**: The utility layer catches input errors (e.g., typing letters instead of numbers), clears the buffer, and prompts again, guaranteeing console resilience.

## Build and Testing

The project uses CMake and includes an automated test suite.

### Building
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running the Simulator
```bash
./vending
```

### Running Tests
The project includes a suite of unit tests verifying the Greedy Algorithm and encapsulation logic.
```bash
./test_vending
```
