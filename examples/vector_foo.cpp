// ----------------------------------------------------------------------------------------------------------
/// @file   vector_foo.cpp
/// @brief  Test cases for Vector.
// ----------------------------------------------------------------------------------------------------------
#define BOOST_TEST_DYN_LINK

#ifdef SEPARATE_TEST
#define BOOST_TEST_MODULE NDArrayTest
#endif

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "ndarray.h"
#define N 7

BOOST_AUTO_TEST_SUITE(VectorTestCases)

BOOST_AUTO_TEST_CASE(VectorBasicBinaryOp) {
  float *a = (float*)malloc(N * sizeof(float));
  float *b = (float*)malloc(N * sizeof(float));
  // bin op add
  for(int i = 0; i<N; ++i) {
    a[i] = b[i] = 1.f;
  }
  ndarray::Vector<float, N> v1(a);
  ndarray::Vector<float, N> v2(b);
  ndarray::Vector<float, N> v3;
  v3 = v1 + v2;
  std::cout << v3;
  BOOST_CHECK(v3[0] == 2.f);
  BOOST_CHECK(v3[1] == 2.f);
  BOOST_CHECK(v3[2] == 2.f);
  BOOST_CHECK(v3[3] == 2.f);
  BOOST_CHECK(v3[4] == 2.f);
  BOOST_CHECK(v3[5] == 2.f);
  BOOST_CHECK(v3[6] == 2.f);

  // bin op sub
  for(int i = 0; i<N; ++i) {
    a[i] = 3.f;
    b[i] = 1.f;
  }
  ndarray::Vector<float, N> v4(a);
  ndarray::Vector<float, N> v5(b);
  ndarray::Vector<float, N> v6;
  v6 = v4 - v5;
  std::cout << v6;
  BOOST_CHECK(v6[0] == 2.f);
  BOOST_CHECK(v6[1] == 2.f);
  BOOST_CHECK(v6[2] == 2.f);
  BOOST_CHECK(v6[3] == 2.f);
  BOOST_CHECK(v6[4] == 2.f);
  BOOST_CHECK(v6[5] == 2.f);
  BOOST_CHECK(v6[6] == 2.f);
  // bin op mul
  ndarray::Vector<float, N> v7;
  v7 = v4 * v5;
  std::cout << v7;
  BOOST_CHECK(v7[0] == 3.f);
  BOOST_CHECK(v7[1] == 3.f);
  BOOST_CHECK(v7[2] == 3.f);
  BOOST_CHECK(v7[3] == 3.f);
  BOOST_CHECK(v7[4] == 3.f);
  BOOST_CHECK(v7[5] == 3.f);
  BOOST_CHECK(v7[6] == 3.f);

  // bin op div
  ndarray::Vector<float, N> v8;
  v8 = v4 / v5;
  std::cout << v8;
  BOOST_CHECK(v8[0] == 3.f);
  BOOST_CHECK(v8[1] == 3.f);
  BOOST_CHECK(v8[2] == 3.f);
  BOOST_CHECK(v8[3] == 3.f);
  BOOST_CHECK(v8[4] == 3.f);
  BOOST_CHECK(v8[5] == 3.f);
  BOOST_CHECK(v8[6] == 3.f);
  
  // bin op max
  ndarray::Vector<float, N> v9;
  v9 = max(v4, v5);
  std::cout << v9;
  BOOST_CHECK(v9[0] == 3.f);
  BOOST_CHECK(v9[1] == 3.f);
  BOOST_CHECK(v9[2] == 3.f);
  BOOST_CHECK(v9[3] == 3.f);
  BOOST_CHECK(v9[4] == 3.f);
  BOOST_CHECK(v9[5] == 3.f);
  BOOST_CHECK(v9[6] == 3.f);
  
  // bin op min
  ndarray::Vector<float, N> v10;
  v10 = min(v4, v5);
  std::cout << v10;
  BOOST_CHECK(v10[0] == 1.f);
  BOOST_CHECK(v10[1] == 1.f);
  BOOST_CHECK(v10[2] == 1.f);
  BOOST_CHECK(v10[3] == 1.f);
  BOOST_CHECK(v10[4] == 1.f);
  BOOST_CHECK(v10[5] == 1.f);
  BOOST_CHECK(v10[6] == 1.f);
  free(a);
  free(b);
}

BOOST_AUTO_TEST_CASE(VectorBasicUnaryOp) {
  float *a = (float*)malloc(N * sizeof(float));
  // unary op sqrt
  for(int i = 0; i<N; ++i) {
    a[i] = 9.f;
  }
  ndarray::Vector<float, N> v1(a);
  ndarray::Vector<float, N> v2;
  v2 = sqrt(v1);
  std::cout << v2;
  BOOST_CHECK(v2[0] == 3.f);
  BOOST_CHECK(v2[1] == 3.f);
  BOOST_CHECK(v2[2] == 3.f);
  BOOST_CHECK(v2[3] == 3.f);
  BOOST_CHECK(v2[4] == 3.f);
  BOOST_CHECK(v2[5] == 3.f);
  BOOST_CHECK(v2[6] == 3.f);

  // unary op rsqrt
  for(int i = 0; i<N; ++i) {
    a[i] = 16.f;
  }
  ndarray::Vector<float, N> v3(a);
  ndarray::Vector<float, N> v4;
  v4 = rsqrt(v3);
  std::cout << v4;
  BOOST_CHECK(std::abs(v4[0] - 0.25f) <= 1e-3);
  BOOST_CHECK(std::abs(v4[1] - 0.25f) <= 1e-3);
  BOOST_CHECK(std::abs(v4[2] - 0.25f) <= 1e-3);
  BOOST_CHECK(std::abs(v4[3] - 0.25f) <= 1e-3);
  BOOST_CHECK(std::abs(v4[4] - 0.25f) <= 1e-3);
  BOOST_CHECK(std::abs(v4[5] - 0.25f) <= 1e-3);
  BOOST_CHECK(std::abs(v4[6] - 0.25f) <= 1e-3);
  free(a);
}
BOOST_AUTO_TEST_SUITE_END()
