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
}
BOOST_AUTO_TEST_SUITE_END()
