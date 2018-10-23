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

BOOST_AUTO_TEST_CASE(VectorBasic) {
  float *a = (float*)malloc(N * sizeof(float));
  float *b = (float*)malloc(N * sizeof(float));
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
}

BOOST_AUTO_TEST_SUITE_END()
