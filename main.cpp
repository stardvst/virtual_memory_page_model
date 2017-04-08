#include <exception>
#include <iostream>
#include "Virtual_memory.hpp"
#include "V_addr.hpp"


int main() {

  Virtual_memory vm;

  V_addr add1 = vm.allocate(20);
  V_addr add2 = vm.allocate(12);
  V_addr add3 = vm.allocate(4);

  try {
    vm.free(add2);
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  try {
    vm[add1] = 4;
    std::cout << static_cast<int>(static_cast<const Virtual_memory>(vm)[add1]) << '\n'; // call const operator[]
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  try {
    vm.free(add3);
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  try {
    vm[add3] = 5;
  } catch(const std::exception& e) {
    std::cerr << e.what();
  }

  std::cin.get();
  return 0;
}
