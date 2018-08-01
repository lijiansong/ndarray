// ----------------------------------------------------------------------------------------------------------
/// @file   ndarray_foo.cpp
/// @brief  Test cases for NDArray.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK

#ifdef SEPARATE_TEST
#define BOOST_TEST_MODULE NDArrayTest
#endif

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "ndarray.h"

BOOST_AUTO_TEST_SUITE(NDArrayTestCases)

BOOST_AUTO_TEST_CASE(NDarrayBasic) {
  using static_ndarray = ndarray::NDArray<int, 48, 3, 32, 32>;
  static_ndarray A;
  auto dim_sizes_a = A.dim_sizes();
  BOOST_CHECK(dim_sizes_a[0] == 48);
  BOOST_CHECK(dim_sizes_a[1] == 3);
  BOOST_CHECK(dim_sizes_a[2] == 32);
  BOOST_CHECK(dim_sizes_a[3] == 32);

  BOOST_CHECK(A.size() == 48 * 3 * 32 * 32);
  BOOST_CHECK(A.rank() == 4);
  BOOST_CHECK(A.dim_size(0) == 48);
  BOOST_CHECK(A.dim_size(1) == 3);
  BOOST_CHECK(A.dim_size(2) == 32);
  BOOST_CHECK(A.dim_size(3) == 32);

  using dynamic_ndarray = ndarray::NDArray<int>;
  dynamic_ndarray B(3);
  BOOST_CHECK(B.rank() == 3);
  dynamic_ndarray C{32, 7, 32, 48};
  auto dim_sizes_c = C.dim_sizes();
  BOOST_CHECK(dim_sizes_c[0] == 32);
  BOOST_CHECK(dim_sizes_c[1] == 7);
  BOOST_CHECK(dim_sizes_c[2] == 32);
  BOOST_CHECK(dim_sizes_c[3] == 48);
  BOOST_CHECK(C.dim_size(0) == 32);
  BOOST_CHECK(C.dim_size(1) == 7);
  BOOST_CHECK(C.dim_size(2) == 32);
  BOOST_CHECK(C.dim_size(3) == 48);
  BOOST_CHECK(C.rank() == 4);
  BOOST_CHECK(C.size() == 32 * 7 * 32 * 48);
}

BOOST_AUTO_TEST_CASE(NDarrayConstructors) {
  // static NDArray
  ndarray::NDArray<int, 48, 3, 32, 32> A;
  auto dim_sizes_a = A.dim_sizes();
  BOOST_CHECK(dim_sizes_a[0] == 48);
  BOOST_CHECK(dim_sizes_a[1] == 3);
  BOOST_CHECK(dim_sizes_a[2] == 32);
  BOOST_CHECK(dim_sizes_a[3] == 32);
  BOOST_CHECK(A.size() == 48 * 3 * 32 * 32);
  BOOST_CHECK(A.rank() == 4);
  BOOST_CHECK(A.dim_size(0) == 48);
  BOOST_CHECK(A.dim_size(1) == 3);
  BOOST_CHECK(A.dim_size(2) == 32);
  BOOST_CHECK(A.dim_size(3) == 32);

  std::array<float, 6> tmp{1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  ndarray::NDArray<float, 3, 2, 1, 1> B(tmp);
  std::cout << B;
  BOOST_CHECK(B.rank() == 4);
  BOOST_CHECK(B.size() == 6);

  ndarray::NDArray<double, 2, 2> C{1.0, 2.8, 3.7, 4.99};
  std::cout << C;
  BOOST_CHECK(C.rank() == 2);
  BOOST_CHECK(C.size() == 4);
  BOOST_CHECK(C[3] == 4.99);
  BOOST_CHECK(C(1, 1) == 4.99);
  BOOST_CHECK(C.dim_size(0) == 2);
  BOOST_CHECK(C.dim_size(1) == 2);
  BOOST_CHECK(C.dim_sizes()[0] == 2);
  BOOST_CHECK(C.dim_sizes()[1] == 2);

  auto D = B;
  BOOST_CHECK(D.rank() == 4);
  BOOST_CHECK(D.size() == 6);
  BOOST_CHECK(D[0] == 1.f);
  BOOST_CHECK(D(0, 0, 0, 0) == 1.f);

  ndarray::NDArray<float, 3, 2, 1, 1> E(B);
  BOOST_CHECK(E.rank() == 4);
  BOOST_CHECK(E.size() == 6);
  BOOST_CHECK(E[0] == 1.f);
  BOOST_CHECK(E(0, 0, 0, 0) == 1.f);

  auto F(B);
  BOOST_CHECK(F.rank() == 4);
  BOOST_CHECK(F.size() == 6);
  BOOST_CHECK(F[0] == 1.f);
  BOOST_CHECK(F(0, 0, 0, 0) == 1.f);

  // dynamic NDArray
  ndarray::NDArray<int> G(3);
  BOOST_CHECK(G.rank() == 3);
  std::vector<size_t> dim_size{1, 2, 3};
  std::vector<float> data{1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  ndarray::NDArray<float> H(dim_size, data);
  auto h_data = H.data();
  auto dim = H.dim_sizes();
  BOOST_CHECK(H.rank() == 3);
  BOOST_CHECK(H.size() == 6);
  BOOST_CHECK(H.dim_size(0) == 1);
  BOOST_CHECK(H.dim_size(1) == 2);
  BOOST_CHECK(H.dim_size(2) == 3);
  BOOST_CHECK(dim[0] == 1);
  BOOST_CHECK(dim[1] == 2);
  BOOST_CHECK(dim[2] == 3);
  BOOST_CHECK(h_data[0] == 1.f);
  BOOST_CHECK(h_data[1] == 2.f);
  BOOST_CHECK(h_data[2] == 3.f);
  BOOST_CHECK(h_data[3] == 4.f);
  BOOST_CHECK(h_data[4] == 5.f);
  BOOST_CHECK(h_data[5] == 6.f);

  ndarray::NDArray<float> I({2, 3});
  I(0, 0) = 1.f;
  I(1, 2) = 7.f;
  I[3] = 3.5f;
  BOOST_CHECK(I.rank() == 2);
  BOOST_CHECK(I.size() == 6);
  BOOST_CHECK(I.dim_size(0) == 2);
  BOOST_CHECK(I.dim_size(1) == 3);
  BOOST_CHECK(I[3] == 3.5f);
  BOOST_CHECK(I(0, 0) == 1.f);
  BOOST_CHECK(I(1, 2) == 7.f);
}

BOOST_AUTO_TEST_CASE(NDarrayElementAccess) {
  // static NDArray
  std::array<float, 6> tmp{{1.f, 2.f, 3.f, 4.f, 5.f, 6.f}};
  ndarray::NDArray<float, 3, 2> A(tmp);
  std::cout << A;

  BOOST_CHECK(A.size() == 6);
  BOOST_CHECK(A.rank() == 2);
  BOOST_CHECK(A[0] == 1.f);
  BOOST_CHECK(A[1] == 2.f);
  BOOST_CHECK(A[2] == 3.f);
  BOOST_CHECK(A[3] == 4.f);
  BOOST_CHECK(A[4] == 5.f);
  BOOST_CHECK(A[5] == 6.f);

  BOOST_CHECK(A(0, 0) == 1.f);
  BOOST_CHECK(A(0, 1) == 2.f);
  BOOST_CHECK(A(1, 0) == 3.f);
  BOOST_CHECK(A(1, 1) == 4.f);
  BOOST_CHECK(A(2, 0) == 5.f);
  BOOST_CHECK(A(2, 1) == 6.f);

  BOOST_CHECK(A(0, 0) == A[0]);
  BOOST_CHECK(A(0, 1) == A[1]);
  BOOST_CHECK(A(1, 0) == A[2]);
  BOOST_CHECK(A(1, 1) == A[3]);
  BOOST_CHECK(A(2, 0) == A[4]);
  BOOST_CHECK(A(2, 1) == A[5]);

  A[3] = 3.99f;
  BOOST_CHECK(A[3] == 3.99f);
  A(2, 1) = 99.99f;
  BOOST_CHECK(A(2, 1) == 99.99f);

  // dynamic NDArray
  ndarray::NDArray<float> B({2, 3});
  B(0, 0) = 1.f;
  B(1, 2) = 7.f;
  B[3] = 3.5f;
  BOOST_CHECK(B.rank() == 2);
  BOOST_CHECK(B.size() == 6);
  BOOST_CHECK(B.dim_size(0) == 2);
  BOOST_CHECK(B.dim_size(1) == 3);
  BOOST_CHECK(B[3] == 3.5f);
  BOOST_CHECK(B(0, 0) == 1.f);
  BOOST_CHECK(B(1, 2) == 7.f);
}

BOOST_AUTO_TEST_SUITE_END()
