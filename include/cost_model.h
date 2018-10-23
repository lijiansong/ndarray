#ifndef _COST_MODEL_H_
#define _COST_MODEL_H_

#include "utils.h"
#include "vector_ops.h"

namespace ndarray {

template <typename T> struct count;

struct store_op {};

template <typename T1, typename T2>
struct is_node<utils::tuple<store_op, T1, T2>> {
  static const bool value = true;
};

template <typename T1, typename T2>
utils::tuple<store_op, typename store_type<T1>::type,
             typename store_type<T2>::type>
store(const T1 &a, const T2 &b) {
  return utils::tuple<store_op, typename store_type<T1>::type,
                      typename store_type<T2>::type>(store_op(), a, b);
}

#include "simd_vectorizer.h"

#include "loops.h"

template <typename vector_model, typename scalar_model, typename T1>
typename std::enable_if<is_node<T1>::value, void>::type execute(T1 expr,
                                                                size_t N) {
  using stats = count<T1>;
  loop<(vector_model::registers - stats::immediates) /
       (stats::loads == 0 ? 1 : stats::loads)>::template execute<vector_model,
                                                                 scalar_model>(
      expr, N);
}

template <typename vector_model, typename scalar_model, size_t N, typename T1>
typename std::enable_if<is_node<T1>::value, void>::type
static_execute(T1 expr) {
  using stats = count<T1>;
  short_loop<vector_model, scalar_model,
             (vector_model::registers - stats::immediates) /
                 (stats::loads == 0 ? 1 : stats::loads),
             N>::template execute<>(expr);
}

} // end of namespace ndarray

#endif // _COST_MODEL_H_
