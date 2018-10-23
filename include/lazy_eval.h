#ifndef _LAZY_EVAL_H_
#define _LAZY_EVAL_H_

#include "utils.h"

namespace ndarray {

template <typename T, size_t N> class VectorInterface;

template <typename T, size_t N> struct is_node<VectorInterface<T, N>> {
  static const bool value = true;
};
template <typename T> struct count {
  static const int loads = 0;
  static const int stores = 0;
  static const int operations = 0;
  static const int immediates = 1;
};

template <typename T, size_t N> struct count<const VectorInterface<T, N> &> {
  static const int loads = 1;
  static const int stores = 0;
  static const int operations = 0;
  static const int immediates = 0;
};

template <typename T1, typename T2>
struct count<utils::tuple<store_op, T1, T2>> {
  static const int loads = count<T2>::loads;
  static const int stores = count<T2>::stores + 1;
  static const int operations = count<T2>::operations;
  static const int immediates = count<T2>::immediates;
};

template <typename op, typename T1> struct count<utils::tuple<op, T1>> {
  static const int loads = count<T1>::loads;
  static const int stores = count<T1>::stores;
  static const int operations = count<T1>::operations + 1;
  static const int immediates = count<T1>::immediates;
};

template <typename op, typename T1, typename T2>
struct count<utils::tuple<op, T1, T2>> {
  static const int loads = count<T1>::loads + count<T2>::loads;
  static const int stores = count<T1>::stores + count<T2>::stores;
  static const int operations =
      count<T1>::operations + count<T2>::operations + 1;
  static const int immediates = count<T1>::immediates + count<T2>::immediates;
};

template <typename T, typename U, typename model> struct vector_evaluator {
  using return_type = typename model::pack_type;
  return_type tmp;
  void prepare(const T &node) { tmp = model::set(node); }
  void load(const T &, const U &) {}
  void store(const T &, const U &) {}
  return_type operator()(const T &, const U &) { return tmp; }
};

template <typename T, size_t N, typename U, typename model>
struct vector_evaluator<const VectorInterface<T, N> &, U, model> {
  using return_type = typename model::pack_type;
  return_type tmp;
  typename VectorInterface<T, N>::const_pointer ptr;
  void prepare(const VectorInterface<T, N> &node) { ptr = node.data(); }
  void load(const VectorInterface<T, N> &, const U &data_size) {
    tmp = model::load(ptr, data_size);
  }
  void store(const VectorInterface<T, N> &, const U &) {}
  return_type operator()(const VectorInterface<T, N> &, const U &) {
    return tmp;
  }
};

template <typename T1, typename T2, typename U, typename model>
struct vector_evaluator<utils::tuple<store_op, T1, T2>, U, model> {
  using return_type = typename model::pack_type;
  return_type tmp;
  T1 ptr;

  vector_evaluator<T2, U, model> right;

  void prepare(const utils::tuple<store_op, T1, T2> &node) {
    right.prepare(utils::get<2>(node));
    ptr = utils::get<1>(node);
  }
  void load(const utils::tuple<store_op, T1, T2> &node, const U &data_size) {
    right.load(utils::get<2>(node), data_size);
  }
  void store(const utils::tuple<store_op, T1, T2> &node, const U &data_size) {
    right.store(utils::get<2>(node), data_size);
    model::store(ptr, data_size, tmp);
  }
  return_type operator()(const utils::tuple<store_op, T1, T2> &node,
                         const U &data_size) {
    return tmp = right(utils::get<2>(node), data_size);
  }
};

template <typename op, typename T1, typename U, typename model>
struct vector_evaluator<utils::tuple<op, T1>, U, model> {
  using return_type = typename model::pack_type;
  vector_evaluator<T1, U, model> child;

  void prepare(const utils::tuple<op, T1> &node) {
    child.prepare(utils::get<1>(node));
  }
  void load(const utils::tuple<op, T1> &node, const U &data_size) {
    child.load(utils::get<1>(node), data_size);
  }
  void store(const utils::tuple<op, T1> &node, const U &data_size) {
    child.store(utils::get<1>(node), data_size);
  }
  return_type operator()(const utils::tuple<op, T1> &node, const U &data_size) {
    return model::template unary<op>(child(utils::get<1>(node), data_size));
  }
};

template <typename op, typename LHS, typename RHS, typename U, typename model>
struct vector_evaluator<utils::tuple<op, LHS, RHS>, U, model> {
  using return_type = typename model::pack_type;
  vector_evaluator<LHS, U, model> left;
  vector_evaluator<RHS, U, model> right;

  void prepare(const utils::tuple<op, LHS, RHS> &node) {
    //LOG();
    left.prepare(utils::get<1>(node));
    right.prepare(utils::get<2>(node));
  }
  void load(const utils::tuple<op, LHS, RHS> &node, const U &data_size) {
    left.load(utils::get<1>(node), data_size);
    right.load(utils::get<2>(node), data_size);
  }
  void store(const utils::tuple<op, LHS, RHS> &node, const U &data_size) {
    left.store(utils::get<1>(node), data_size);
    right.store(utils::get<2>(node), data_size);
  }
  return_type operator()(const utils::tuple<op, LHS, RHS> &node,
                         const U &data_size) {
    return model::template binary<op>(left(utils::get<1>(node), data_size),
                                      right(utils::get<2>(node), data_size));
  }
};
} // end of namespace ndarray

#endif // _LAZY_EVAL_H_
