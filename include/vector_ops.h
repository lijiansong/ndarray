#ifndef _VECTOR_OPS_H_
#define _VECTOR_OPS_H_

#include "utils.h"

namespace ndarray {

template <typename T> struct is_node { static const bool value = false; };

template <typename T> struct store_type {
  typedef typename std::conditional<std::is_fundamental<T>::value ||
                                        std::is_pointer<T>::value,
                                    T, const T &>::type type;
};

#define GEN_VECTOR_BINARY_OP(OP_NAME, OP)                                      \
  struct OP {};                                                                \
  template <typename T1, typename T2>                                          \
  struct is_node<utils::tuple<OP, T1, T2>> {                                   \
    static const bool value = true;                                            \
  };                                                                           \
  template <typename T1, typename T2>                                          \
  struct store_type<utils::tuple<OP, T1, T2>> {                                \
    typedef utils::tuple<OP, T1, T2> type;                                     \
  };                                                                           \
  template <typename T1, typename T2>                                          \
  typename std::enable_if<is_node<T1>::value || is_node<T2>::value,            \
                          utils::tuple<OP, typename store_type<T1>::type,      \
                                         typename store_type<T2>::type>>::type \
  OP_NAME(const T1 &a, const T2 &b) {                                          \
    return utils::tuple<OP, typename store_type<T1>::type,                     \
                          typename store_type<T2>::type>(OP(), a, b);          \
  }

GEN_VECTOR_BINARY_OP(operator+, add_op)
GEN_VECTOR_BINARY_OP(operator-, sub_op)
GEN_VECTOR_BINARY_OP(operator*, mul_op)
GEN_VECTOR_BINARY_OP(operator/, div_op)
GEN_VECTOR_BINARY_OP(min, min_op)
GEN_VECTOR_BINARY_OP(max, max_op)

#define GEN_VECTOR_UNARY_OP(OP_NAME, OP)                                       \
  struct OP {};                                                                \
  template <typename T1> struct is_node<utils::tuple<OP, T1>> {                \
    static const bool value = true;                                            \
  };                                                                           \
  template <typename T1> struct store_type<utils::tuple<OP, T1>> {             \
    typedef utils::tuple<OP, T1> type;                                         \
  };                                                                           \
  template <typename T1>                                                       \
  typename std::enable_if<                                                     \
      is_node<T1>::value,                                                      \
      utils::tuple<OP, typename store_type<T1>::type>>::type                   \
  OP_NAME(const T1 &a) {                                                       \
    return utils::tuple<OP, typename store_type<T1>::type>(OP(), a);           \
  }

GEN_VECTOR_UNARY_OP(sqrt, sqrt_op)
GEN_VECTOR_UNARY_OP(rsqrt, rsqrt_op)

} // end of namespace ndarray

#endif // _VECTOR_OPS_H_
