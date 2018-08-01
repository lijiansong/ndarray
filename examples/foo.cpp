#include <iostream>
#include "ndarray.h"

int main() {
  std::cout << "--------------- dynamic ndarray ---------------\n";
  std::vector<size_t> dim{1, 2, 3};
  std::vector<int> data{1, 2, 3, 4, 5, 6};
  ndarray::NDArray<int> C(dim, data);
  std::cout << "(0, 0, 0):\n" << C(0, 0, 0) << std::endl;
  std::cout << "(0, 0, 1):\n" << C(0, 0, 1) << std::endl;
  std::cout << "(0, 0, 2):\n" << C(0, 0, 2) << std::endl;
  std::cout << "(0, 1, 0):\n" << C(0, 1, 0) << std::endl;
  std::cout << "(0, 1, 1):\n" << C(0, 1, 1) << std::endl;
  std::cout << "(0, 1, 2):\n" << C(0, 1, 2) << std::endl;
  std::cout << "--------------- static ndarray ---------------\n";
  ndarray::NDArray<int, 1, 2, 3> A {1, 2, 3, 4, 5, 6};
  std::cout << "(0, 0, 0):\n" << A(0, 0, 0) << std::endl;
  std::cout << "(0, 0, 1):\n" << A(0, 0, 1) << std::endl;
  std::cout << "(0, 0, 2):\n" << A(0, 0, 2) << std::endl;
  std::cout << "(0, 1, 0):\n" << A(0, 1, 0) << std::endl;
  std::cout << "(0, 1, 1):\n" << A(0, 1, 1) << std::endl;
  std::cout << "(0, 1, 2):\n" << A(0, 1, 2) << std::endl;
  return 0;
}
