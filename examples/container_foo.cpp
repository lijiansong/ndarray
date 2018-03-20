#include "ndarray/ndarray_container.h"
#include <iostream>

void test1() {
    ndarray::NDArrayContainer<int, 32, 3, 32, 48> A;
    std::cout << A.size() << '\n'; // 32*3*32*48

    ndarray::NDArrayContainer<int, 1> B;
    std::cout << B.size() << '\n'; // 1
}

int main() {
    test1();
    return 0;
}
