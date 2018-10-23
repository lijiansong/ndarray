#ifndef _VECTOR_DYNAMIC_H_
#define _VECTOR_DYNAMIC_H_

#include <algorithm>
#include <cmath>
#include <memory>
#include <type_traits>

#include "cost_model.h"
#include "lazy_eval.h"
#include "utils.h"
#include "vector_ops.h"

namespace ndarray {

template <typename T> class VectorInterface<T, 0> {
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

  VectorInterface(size_t size, T val = T())
      : size_(size), data_(static_cast<T *>(_mm_malloc(
                               size_ * sizeof(T), vector_model::alignment)),
                           &_mm_free) {
    std::fill(data_.get(), data_.get() + size_, val);
  }

  size_type size() const { return size_; }
  pointer data() { return data_.get(); }
  const_pointer data() const { return data_.get(); }
  reference operator[](size_type i) { return data_[i]; }
  const_reference operator[](size_type i) const { return data_[i]; }
  iterator begin() { return data_.get(); }
  iterator end() { return data_.get() + size_; }
  const_iterator begin() const { return data_.get(); }
  const_iterator end() const { return data_.get() + size_; }
  void swap(VectorInterface &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
  }

  VectorInterface &operator=(const VectorInterface &rhs) {
    execute<vector_model, scalar_model>(store(data_.get(), rhs), size_);
    return *this;
  }

  template <typename T1> VectorInterface &operator=(const T1 &rhs) {
    execute<vector_model, scalar_model>(store(data_.get(), rhs), size_);
    return *this;
  }

  template <typename T1> VectorInterface &operator+=(const T1 &rhs) {
    execute<vector_model, scalar_model>(store(data_.get(), *this + rhs), size_);
    return *this;
  }

  template <typename T1> VectorInterface &operator-=(const T1 &rhs) {
    execute<vector_model, scalar_model>(store(data_.get(), *this - rhs), size_);
    return *this;
  }

  template <typename T1> VectorInterface &operator*=(const T1 &rhs) {
    execute<vector_model, scalar_model>(store(data_.get(), *this * rhs), size_);
    return *this;
  }

  template <typename T1> VectorInterface &operator/=(const T1 &rhs) {
    execute<vector_model, scalar_model>(store(data_.get(), *this / rhs), size_);
    return *this;
  }

private:
  VectorInterface(const VectorInterface &) = delete;

  const size_type size_;
  std::unique_ptr<value_type[], void (*)(void *)> data_;
};

} // end of namespace ndarray

#endif // _VECTOR_DYNAMIC_H_
