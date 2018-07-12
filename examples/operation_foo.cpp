// ----------------------------------------------------------------------------------------------------------
/// @file   operations_foo.cpp
/// @brief  Test cases for NDArray operations.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK

#ifdef SEPARATE_TEST
#define BOOST_TEST_MODULE NDArrayOperations
#endif

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "ndarray/ndarray.h"

BOOST_AUTO_TEST_SUITE(NDArrayOperationsTest)

BOOST_AUTO_TEST_CASE(NDarrayAdd) {
  ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
  ndarray::NDArray<int, 2, 2, 1> B{1, 2, 3, 4};

  auto C = A + B;
  ndarray::NDArray<int, 2, 2, 1> D = A + B;

  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(D.size() == 4);
  BOOST_CHECK(C(0, 0, 0) == 2);
  BOOST_CHECK(D(0, 0, 0) == 2);
  BOOST_CHECK(C[0] == 2);
  BOOST_CHECK(D[0] == 2);
  BOOST_CHECK(C[1] == 4);
  BOOST_CHECK(D[1] == 4);
  BOOST_CHECK(C[2] == 6);
  BOOST_CHECK(D[2] == 6);
  BOOST_CHECK(C[3] == 8);
  BOOST_CHECK(D[3] == 8);

  ndarray::NDArray<float> E{2, 2};
  E[0] = 1.f;
  E[1] = 2.f;
  E[2] = 3.f;
  E[3] = 4.f;
  ndarray::NDArray<float> F{2, 2};
  F[0] = 1.f;
  F[1] = 2.f;
  F[2] = 3.f;
  F[3] = 4.f;
  auto G = E + F;
  // std::cout << G;
  BOOST_CHECK(G[0] == 2.f);
  BOOST_CHECK(G[1] == 4.f);
  BOOST_CHECK(G[2] == 6.f);
  BOOST_CHECK(G[3] == 8.f);
  BOOST_CHECK(G(0, 0) == 2.f);
  BOOST_CHECK(G(1, 1) == 8.f);
  ndarray::NDArray<float> H = E + F;
  std::cout << H;
  BOOST_CHECK(H[0] == 2.f);
  BOOST_CHECK(H[1] == 4.f);
  BOOST_CHECK(H[2] == 6.f);
  BOOST_CHECK(H[3] == 8.f);
  BOOST_CHECK(H(0, 0) == 2.f);
  BOOST_CHECK(H(1, 1) == 8.f);
}

BOOST_AUTO_TEST_CASE(NDarraySub) {
  ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
  ndarray::NDArray<int, 2, 2, 1> B{2, 4, 6, 8};

  auto C = A - B;
  ndarray::NDArray<int, 2, 2, 1> D = A - B;

  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(D.size() == 4);
  BOOST_CHECK(C[0] == -1);
  BOOST_CHECK(C[1] == -2);
  BOOST_CHECK(C[2] == -3);
  BOOST_CHECK(C[3] == -4);
  BOOST_CHECK(D(0, 0, 0) == -1);
  BOOST_CHECK(D(0, 1, 0) == -2);
  BOOST_CHECK(D(1, 0, 0) == -3);
  BOOST_CHECK(D(1, 1, 0) == -4);
  ndarray::NDArray<float> E{2, 2};
  E[0] = 4.f;
  E[1] = 3.f;
  E[2] = 2.f;
  E[3] = 1.f;
  ndarray::NDArray<float> F{2, 2};
  F[0] = 1.f;
  F[1] = 2.f;
  F[2] = 3.f;
  F[3] = 4.f;
  auto G = E - F;
  // std::cout << G;
  BOOST_CHECK(G[0] == 3.f);
  BOOST_CHECK(G[1] == 1.f);
  BOOST_CHECK(G[2] == -1.f);
  BOOST_CHECK(G[3] == -3.f);
  ndarray::NDArray<float> H = E - F;
  std::cout << H;
  BOOST_CHECK(H[0] == 3.f);
  BOOST_CHECK(H[1] == 1.f);
  BOOST_CHECK(H[2] == -1.f);
  BOOST_CHECK(H[3] == -3.f);
  BOOST_CHECK(H(0, 0) == 3.f);
  BOOST_CHECK(H(1, 1) == -3.f);
}

BOOST_AUTO_TEST_CASE(NDarrayMul) {
  ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
  ndarray::NDArray<int, 2, 2, 1> B{1, 2, 3, 4};
  auto C = A * B;
  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(C.rank() == 3);
  BOOST_CHECK(C[0] == 1);
  BOOST_CHECK(C(0, 0, 0) == 1);
  BOOST_CHECK(C(0, 1, 0) == 4);
  BOOST_CHECK(C(1, 0, 0) == 9);
  BOOST_CHECK(C(1, 1, 0) == 16);

  ndarray::NDArray<float> E{2, 2};
  E[0] = 1.f;
  E[1] = 2.f;
  E[2] = 3.f;
  E[3] = 4.f;
  ndarray::NDArray<float> F{2, 2};
  F[0] = 1.f;
  F[1] = 2.f;
  F[2] = 3.f;
  F[3] = 4.f;
  auto G = E * F;
  // std::cout << G;
  BOOST_CHECK(G[0] == 1.f);
  BOOST_CHECK(G[1] == 4.f);
  BOOST_CHECK(G[2] == 9.f);
  BOOST_CHECK(G[3] == 16.f);
  BOOST_CHECK(G(0, 0) == 1.f);
  BOOST_CHECK(G(1, 1) == 16.f);
  ndarray::NDArray<float> H = E * F;
  std::cout << H;
  BOOST_CHECK(H[0] == 1.f);
  BOOST_CHECK(H[1] == 4.f);
  BOOST_CHECK(H[2] == 9.f);
  BOOST_CHECK(H[3] == 16.f);
  BOOST_CHECK(H(0, 0) == 1.f);
  BOOST_CHECK(H(1, 1) == 16.f);
}

BOOST_AUTO_TEST_CASE(NDarrayOperationPriority) {
  ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
  ndarray::NDArray<int, 2, 2, 1> B{4, 3, 4, 1};

  auto C = A + A * B;
  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(C.rank() == 3);
  BOOST_CHECK(C[0] == 5);
  BOOST_CHECK(C[1] == 8);
  BOOST_CHECK(C[2] == 15);
  BOOST_CHECK(C[3] == 8);

  auto D = (A + A) * B;
  BOOST_CHECK(D.size() == 4);
  BOOST_CHECK(D.rank() == 3);
  BOOST_CHECK(D[0] == 8);
  BOOST_CHECK(D[1] == 12);
  BOOST_CHECK(D[2] == 24);
  BOOST_CHECK(D[3] == 8);

  auto E = A - A * B;
  BOOST_CHECK(E.size() == 4);
  BOOST_CHECK(E.rank() == 3);
  BOOST_CHECK(E[0] == -3);
  BOOST_CHECK(E[1] == -4);
  BOOST_CHECK(E[2] == -9);
  BOOST_CHECK(E[3] == 0);

  auto F = A * B - A;
  BOOST_CHECK(F.size() == 4);
  BOOST_CHECK(F.rank() == 3);
  BOOST_CHECK(F[0] == 3);
  BOOST_CHECK(F[1] == 4);
  BOOST_CHECK(F[2] == 9);
  BOOST_CHECK(F[3] == 0);

  ndarray::NDArray<int> _A{2, 2};
  _A[0] = 1;
  _A[1] = 2;
  _A[2] = 3;
  _A[3] = 4;
  ndarray::NDArray<int> _B{2, 2};
  _B[0] = 4;
  _B[1] = 3;
  _B[2] = 4;
  _B[3] = 1;

  auto _C = _A + _A * _B;
  BOOST_CHECK(_C.size() == 4);
  BOOST_CHECK(_C.rank() == 2);
  BOOST_CHECK(_C[0] == 5);
  BOOST_CHECK(_C[1] == 8);
  BOOST_CHECK(_C[2] == 15);
  BOOST_CHECK(_C[3] == 8);

  auto _D = (_A + _A) * _B;
  BOOST_CHECK(_D.size() == 4);
  BOOST_CHECK(_D.rank() == 2);
  BOOST_CHECK(_D[0] == 8);
  BOOST_CHECK(_D[1] == 12);
  BOOST_CHECK(_D[2] == 24);
  BOOST_CHECK(_D[3] == 8);

  auto _E = _A - _A * _B;
  BOOST_CHECK(_E.size() == 4);
  BOOST_CHECK(_E.rank() == 2);
  BOOST_CHECK(_E[0] == -3);
  BOOST_CHECK(_E[1] == -4);
  BOOST_CHECK(_E[2] == -9);
  BOOST_CHECK(_E[3] == 0);

  auto _F = _A * _B - _A;
  BOOST_CHECK(_F.size() == 4);
  BOOST_CHECK(_F.rank() == 2);
  BOOST_CHECK(_F[0] == 3);
  BOOST_CHECK(_F[1] == 4);
  BOOST_CHECK(_F[2] == 9);
  BOOST_CHECK(_F[3] == 0);
}

BOOST_AUTO_TEST_CASE(NDarrayGlobalReduction) {
  // static NDArray
  ndarray::NDArray<int, 1, 2, 3> A{1, 2, 3, 4, 5, 6};
  BOOST_CHECK(A.sum() == 21);
  BOOST_CHECK(A.max() == 6);
  BOOST_CHECK(A.min() == 1);

  ndarray::NDArray<float, 2, 3> B{1.f, -2.2f, -3.f, 2.2f, 3.f, 4.99f};
  BOOST_CHECK(B.sum() == 5.99f);
  BOOST_CHECK(B.max() == 4.99f);
  BOOST_CHECK(B.min() == -3.f);

  // dynamic NDArray
  ndarray::NDArray<int> _A{2, 3};
  _A[0] = 1;
  _A[1] = 2;
  _A[2] = 3;
  _A[3] = 4;
  _A[4] = 5;
  _A[5] = 6;
  BOOST_CHECK(_A.sum() == 21);
  BOOST_CHECK(_A.max() == 6);
  BOOST_CHECK(_A.min() == 1);

  std::vector<float> b{1.f, -2.2f, -3.f, 2.2f, 3.f, 4.99f};
  std::vector<size_t> dim{2, 3};
  ndarray::NDArray<float> _B(dim, b);
  BOOST_CHECK(B.sum() == 5.99f);
  BOOST_CHECK(B.max() == 4.99f);
  BOOST_CHECK(B.min() == -3.f);
}

BOOST_AUTO_TEST_CASE(NDarrayReshape) {
  ndarray::NDArray<int, 1, 2, 3> A{1, 2, 3, 4, 5, 6};
  auto dim_sizes_a = A.dim_sizes();
  BOOST_CHECK(dim_sizes_a[0] == 1);
  BOOST_CHECK(dim_sizes_a[1] == 2);
  BOOST_CHECK(dim_sizes_a[2] == 3);
  BOOST_CHECK(A.dim_size(0) == 1);
  BOOST_CHECK(A.dim_size(1) == 2);
  BOOST_CHECK(A.dim_size(2) == 3);
  BOOST_CHECK(A.rank() == 3);
  BOOST_CHECK(A.size() == 6);
  BOOST_CHECK(A[0] == 1);
  BOOST_CHECK(A[1] == 2);
  BOOST_CHECK(A[2] == 3);
  BOOST_CHECK(A[3] == 4);
  BOOST_CHECK(A[4] == 5);
  BOOST_CHECK(A[5] == 6);
  std::cout << A(0, 1, 0) << std::endl;
  std::cout << A(0, 1, 1) << std::endl;
  std::cout << A(0, 1, 2) << std::endl;
  BOOST_CHECK(A(0, 0, 0) == A[0]);
  BOOST_CHECK(A(0, 0, 1) == A[1]);
  BOOST_CHECK(A(0, 0, 2) == A[2]);
  BOOST_CHECK(A(0, 1, 0) == A[3]);
  BOOST_CHECK(A(0, 1, 1) == A[4]);
  BOOST_CHECK(A(0, 1, 2) == A[5]);

  auto B = A.reshape<3, 2>();
  auto dim_sizes_b = B.dim_sizes();
  BOOST_CHECK(dim_sizes_b[0] == 3);
  BOOST_CHECK(dim_sizes_b[1] == 2);

  BOOST_CHECK(B.dim_size(0) == 3);
  BOOST_CHECK(B.dim_size(1) == 2);
  BOOST_CHECK(B.rank() == 2);
  BOOST_CHECK(B.size() == 6);
  BOOST_CHECK(B[0] == 1);
  BOOST_CHECK(B[1] == 2);
  BOOST_CHECK(B[2] == 3);
  BOOST_CHECK(B[3] == 4);
  BOOST_CHECK(B[4] == 5);
  BOOST_CHECK(B[5] == 6);
  BOOST_CHECK(B(0, 0) == 1);
  BOOST_CHECK(B(0, 1) == 2);
  BOOST_CHECK(B(1, 0) == 3);
  BOOST_CHECK(B(1, 1) == 4);
  BOOST_CHECK(B(2, 0) == 5);
  BOOST_CHECK(B(2, 1) == 6);
}

BOOST_AUTO_TEST_SUITE_END()
