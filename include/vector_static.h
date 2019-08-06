#ifndef VECTOR_STATIC_H
#define VECTOR_STATIC_H

#include <algorithm>
#include <cmath>
#include <memory>
#include <ostream>
#include <type_traits>

#include "cost_model.h"
#include "lazy_eval.h"
#include "utils.h"
#include "vector_ops.h"

namespace ndarray {

template <typename T, size_t size_ = 0> class VectorInterface {
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = T *;
  using const_iterator = const T *;
  using vector_model = vector_inst_set<T>;
  using scalar_model = scalar_inst_set<T>;

  VectorInterface(T val = T()) { std::fill(data_, data_ + size_, val); }

  VectorInterface(pointer ptr) { memcpy(data_, ptr, size_ * sizeof(T)); }

  size_type size() const { return size_; }
  pointer data() { return data_; }
  const_pointer data() const { return data_; }
  reference operator[](size_type i) { return data_[i]; }
  const_reference operator[](size_type i) const { return data_[i]; }
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator begin() const { return data_; }
  const_iterator end() const { return data_ + size_; }
  void swap(VectorInterface &other) { std::swap<size_>(data_, other.data_); }

  VectorInterface &operator=(const VectorInterface &rhs) {
    static_execute<vector_model, scalar_model, size_>(
        store(static_cast<pointer>(data_), rhs));
    return *this;
  }

  template <typename T1> VectorInterface &operator=(const T1 &rhs) {
    static_execute<vector_model, scalar_model, size_>(
        store(static_cast<pointer>(data_), rhs));
    return *this;
  }

  template <typename T1> VectorInterface &operator+=(const T1 &rhs) {
    static_execute<vector_model, scalar_model, size_>(
        store(static_cast<pointer>(data_), *this + rhs));
    return *this;
  }

  template <typename T1> VectorInterface &operator-=(const T1 &rhs) {
    static_execute<vector_model, scalar_model, size_>(
        store(static_cast<pointer>(data_), *this - rhs));
    return *this;
  }

  template <typename T1> VectorInterface &operator*=(const T1 &rhs) {
    static_execute<vector_model, scalar_model, size_>(
        store(static_cast<pointer>(data_), *this * rhs));
    return *this;
  }

  template <typename T1> VectorInterface &operator/=(const T1 &rhs) {
    static_execute<vector_model, scalar_model, size_>(
        store(static_cast<pointer>(data_), *this / rhs));
    return *this;
  }

private:
  VectorInterface(const VectorInterface &) = delete;

  VECTOR_ALIGN(vector_model::alignment) value_type data_[size_];
};

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const VectorInterface<T, N> &v) {
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i] << " ";
  }
  os << '\n';
  return os;
}

} // end of namespace ndarray

#endif // VECTOR_STATIC_H
