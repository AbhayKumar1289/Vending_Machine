# CMake generated Testfile for 
# Source directory: C:/Projects/Vending_Machine_Git
# Build directory: C:/Projects/Vending_Machine_Git/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(VendingTests "C:/Projects/Vending_Machine_Git/build/Debug/test_vending.exe")
  set_tests_properties(VendingTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Projects/Vending_Machine_Git/CMakeLists.txt;15;add_test;C:/Projects/Vending_Machine_Git/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(VendingTests "C:/Projects/Vending_Machine_Git/build/Release/test_vending.exe")
  set_tests_properties(VendingTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Projects/Vending_Machine_Git/CMakeLists.txt;15;add_test;C:/Projects/Vending_Machine_Git/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(VendingTests "C:/Projects/Vending_Machine_Git/build/MinSizeRel/test_vending.exe")
  set_tests_properties(VendingTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Projects/Vending_Machine_Git/CMakeLists.txt;15;add_test;C:/Projects/Vending_Machine_Git/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(VendingTests "C:/Projects/Vending_Machine_Git/build/RelWithDebInfo/test_vending.exe")
  set_tests_properties(VendingTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Projects/Vending_Machine_Git/CMakeLists.txt;15;add_test;C:/Projects/Vending_Machine_Git/CMakeLists.txt;0;")
else()
  add_test(VendingTests NOT_AVAILABLE)
endif()
