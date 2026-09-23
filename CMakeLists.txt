cmake_minimum_required(VERSION 3.10)
project(VendingMachineSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Main executable
add_executable(vending main.cpp)

# Tests
enable_testing()
add_executable(test_vending tests/test_vending.cpp)

# Run tests on build
add_test(NAME VendingTests COMMAND test_vending)
