// ----------------------------------------------------------------------------------------------------------
/// @file   operations_foo.cpp
/// @brief  Test cases for NDArray operations.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK

#ifdef SEPARATE_TEST
#define BOOST_TEST_MODULE NDArrayOperations
#endif

#include <boost/test/unit_test.hpp>

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
}

BOOST_AUTO_TEST_CASE(NDarraySub) {
  ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
  ndarray::NDArray<int, 2, 2, 1> B{2, 4, 6, 8};

  auto C = A - B;
  ndarray::NDArray<int, 2, 2, 1> D = A - B;

  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(D.size() == 4);
  BOOST_CHECK(C[0] == -1);
  BOOST_CHECK(D(0, 0, 0) == -1);
  BOOST_CHECK(C[1] == -2);
  BOOST_CHECK(D(1, 0, 0) == -2);
  BOOST_CHECK(C[2] == -3);
  BOOST_CHECK(D(0, 1, 0) == -3);
  BOOST_CHECK(C[3] == -4);
  BOOST_CHECK(D(1, 1, 0) == -4);
}

BOOST_AUTO_TEST_CASE(NDarrayMul) {
  ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
  ndarray::NDArray<int, 2, 2, 1> B{1, 2, 3, 4};
  auto C = A * B;
  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(C.rank() == 3);
  BOOST_CHECK(C[0] == 1);
  BOOST_CHECK(C(0, 0, 0) == 1);
  BOOST_CHECK(C(0, 1, 0) == 9);
  BOOST_CHECK(C(1, 0, 0) == 4);
  BOOST_CHECK(C(1, 1, 0) == 16);
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
}

BOOST_AUTO_TEST_CASE(NDarrayGlobalReduction) {
  ndarray::NDArray<int, 1, 2, 3> A{1, 2, 3, 4, 5, 6};
  BOOST_CHECK(A.sum() == 21);
  BOOST_CHECK(A.max() == 6);
  BOOST_CHECK(A.min() == 1);

  ndarray::NDArray<float, 2, 3> B{1.f, -2.2f, -3.f, 2.2f, 3.f, 4.99f};
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
  BOOST_CHECK(A(0, 0, 0) == 1);
  BOOST_CHECK(A(0, 0, 1) == 3);
  BOOST_CHECK(A(0, 0, 2) == 5);
  BOOST_CHECK(A(0, 1, 0) == 2);
  BOOST_CHECK(A(0, 1, 1) == 4);
  BOOST_CHECK(A(0, 1, 2) == 6);

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
  BOOST_CHECK(B(0, 1) == 4);
  BOOST_CHECK(B(1, 0) == 2);
  BOOST_CHECK(B(1, 1) == 5);
  BOOST_CHECK(B(2, 0) == 3);
  BOOST_CHECK(B(2, 1) == 6);
}

BOOST_AUTO_TEST_SUITE_END()
