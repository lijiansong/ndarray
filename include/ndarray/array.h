#ifndef ARRAY_H
#define ARRAY_H

#include "error.h"

#include <cstddef>
#include <initializer_list>

namespace array {

// single dimension array
template <typename T, std::size_t N> class Array;

template <typename T, std::size_t N> class Array {
public:
  //------------------------- ALIAS -----------------------------
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using size_type = std::size_t;
  //-------------------------------------------------------------
  struct ForwardIterator {
    bool is_end = false;
    size_type index;
    Array<T, N> *outer;
    bool top_level = true;
    ForwardIterator() : index(0), outer(NULL) {}
    ForwardIterator(Array<T, N> *theOuter) : index(0), outer(theOuter) {}
    ForwardIterator(bool end) : is_end(end), index(N) {}

    T &operator*() const { return outer->_data[index]; }

    bool operator==(const ForwardIterator &it) {
      if (index == it.index && outer == it.outer) {
        return true;
      } else if (index == it.index && is_end && it.is_end && top_level &&
                 it.top_level) {
        return true;
      }
      return false;
    }

    bool operator!=(const ForwardIterator &it) { return !((*this) == it); }

    bool it_inc() {
      if (++index == N) {
        return true;
      }
      return false;
    }

    ForwardIterator &operator++() {
      if (it_inc()) {
        is_end = true;
      }
      return (*this);
    }

    ForwardIterator operator++(int) {
      ForwardIterator it = (*this);
      ++(*this);
      return it;
    }
  };

public:
  //------------------------- ALIAS -----------------------------
  using iterator = ForwardIterator;
  //-------------------------------------------------------------

  //--------------------- Constructors --------------------------
  Array() {
    static_assert((N > 0), "Invalid Array Size!");
    n = N;
  }

  Array(const Array &copy) : n(copy.n) {
    for (size_type i = 0; i < this->n; ++i) {
      this->_data[i] = copy._data[i];
    }
  }

  template <typename U> Array(const Array<U, N> &copy) : n(copy.n) {
    for (size_type i = 0; i < this->n; ++i) {
      this->_data[i] = copy._data[i];
    }
  }

  Array(std::initializer_list<T> list) {
    if (N != list.size()) {
      InvalidInitialListSizeException exception;
      throw exception;
    }
    auto it = list.begin(), ie = list.end();
    size_type i = 0;
    for (; it != ie; ++it, ++i) {
      _data[i] = *it;
    }
  }

  Array &operator=(const Array<T, N> &copy) {
    this->n = copy.n;
    if (&copy == this) {
      return (*this);
    }
    for (size_type i = 0; i < this->n; ++i) {
      this->_data[i] = copy._data[i];
    }
    return (*this);
  }

  template <typename U> Array &operator=(const Array<U, N> &copy) {
    this->n = copy.n;
    for (size_type i = 0; i < this->n; ++i) {
      this->_data[i] = copy._data[i];
    }
    return (*this);
  }

  Array &operator=(std::initializer_list<T> list) {
    if (N != list.size()) {
      InvalidInitialListSizeException exception;
      throw exception;
    }
    this->n = N;
    auto it = list.begin(), ie = list.end();
    size_type i = 0;
    for (; (it != ie) && (i < this->n); ++it, ++i) {
      _data[i] = *it;
    }
    return (*this);
  }
  //-------------------------------------------------------------

  //------------------------ Operators --------------------------
  bool operator!=(const Array<T, N> &array) {
    if (this->n != array.n)
      return true;
    for (size_type i = 0; i < N; ++i) {
      if (this->_data[i] != array._data[i])
        return true;
    }
    return false;
  }

  bool operator==(const Array<T, N> &array) { return !((*this) != array); }
  //-------------------------------------------------------------

  //--------------------- Basic Operations ----------------------
  reference at(size_type pos) {
    if (pos > n) {
      OutOfRangeException exception;
      throw exception;
    }
    return _data[pos];
  }

  const_reference at(size_type pos) const {
    if (pos > n) {
      OutOfRangeException exception;
      throw exception;
    }
    return _data[pos];
  }

  T &operator[](size_type pos) {
    if (pos > n) {
      OutOfRangeException exception;
      throw exception;
    }
    return _data[pos];
  }

  const T &operator[](size_type pos) const {
    if (pos > n) {
      OutOfRangeException exception;
      throw exception;
    }
    return _data[pos];
  }

  reference front() { return _data[0]; }

  reference back() { return _data[(this->n - 1)]; }

  constexpr size_type size() { return N; }

  iterator begin() {
    iterator it(this);
    return it;
  }

  constexpr iterator begin() {
    iterator it(this);
    return it;
  }

  iterator end() {
    iterator it(true);
    return it;
  }

  constexpr iterator end() {
    iterator it(true);
    return it;
  }

  void fill(const T &value) {
    for (size_type i = 0; i < this->n; ++i) {
      _data[i] = value;
    }
  }

  T* data() { return (T*)_data; }

  constexpr const T* data() const { return (T*)_data; }
  //-------------------------------------------------------------

private:
  T _data[N];
  size_type n;
};

// TODO: multiple dimension array

} // end of namespace array

#endif // ARRAY_H
