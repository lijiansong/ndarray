// ----------------------------------------------------------------------------------------------------------
/// @file   traits_foo.cpp
/// @brief  Test suite for traits.
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK

#ifdef SEPARATE_TEST
#define BOOST_TEST_MODULE TraitsTests
#endif

#include <boost/test/unit_test.hpp>

#include "ndarray/ndarray_traits.h"

BOOST_AUTO_TEST_SUITE(NDArrayTraits)

BOOST_AUTO_TEST_CASE(NDarrayTraitsBasic) {
  using traits = ndarray::NDArrayTraits<int, 4, 8>;
  traits::container_type A;
  BOOST_CHECK(A.size() == 32);
}

BOOST_AUTO_TEST_SUITE_END()
