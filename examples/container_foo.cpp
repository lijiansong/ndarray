// ----------------------------------------------------------------------------------------------------------
/// @file   container_foo.cpp
/// @brief  Test cases for container.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK

#ifdef SEPARATE_TEST
#define BOOST_TEST_MODULE ConstainerTests
#endif

#include <array>
#include <boost/test/unit_test.hpp>

#include "ndarray/ndarray_container.h"

BOOST_AUTO_TEST_SUITE(NDArrayConatiner)

BOOST_AUTO_TEST_CASE(NDarrayConatinerBasic) {
  ndarray::NDArrayContainer<int, 4, 8> A;
  BOOST_CHECK(A.size() == 32);
}

BOOST_AUTO_TEST_CASE(NDarrayConatinerConstructor) {
  ndarray::NDArrayContainer<float, 2, 1, 2> A{1.f, 2.5f, 3.f, 4.f};
  BOOST_CHECK(A.size() == 4);
  BOOST_CHECK(A[0] == 1.f);
  BOOST_CHECK(A[1] == 2.5f);
  BOOST_CHECK(A[2] == 3.f);
  BOOST_CHECK(A[3] == 4.f);

  std::array<float, 4> tmp{1.f, 2.5f, 3.f, 4.f};
  ndarray::NDArrayContainer<float, 2, 1, 2> B(tmp);
  BOOST_CHECK(B[0] == 1.f);
  BOOST_CHECK(B[1] == 2.5f);
  BOOST_CHECK(B[2] == 3.f);
  BOOST_CHECK(B[3] == 4.f);
}

BOOST_AUTO_TEST_CASE(NDarrayConatinerIterator) {
  ndarray::NDArrayContainer<float, 2, 1, 2> A{1.f, 2.5f, 3.f, 4.f};
  float a[4];
  auto it = A.begin(), ie = A.end();
  std::size_t i = 0;
  for (; it != ie; ++it, ++i)
    a[i] = *it;
  BOOST_CHECK(A.size() == 4);
  BOOST_CHECK(a[0] == 1.f);
  BOOST_CHECK(a[1] == 2.5f);
  BOOST_CHECK(a[2] == 3.f);
  BOOST_CHECK(a[3] == 4.f);
}

BOOST_AUTO_TEST_SUITE_END()
