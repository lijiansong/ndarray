#ifndef _SIMD_VECTORIZER_H_
#define _SIMD_VECTORIZER_H_

#include <immintrin.h>

template <typename T> struct scalar_inst_set {
  using value_type = T;
  using pack_type = T;
  static const size_t pack_size = 1;
  static const size_t alignment = 16;
  static const size_t registers = 8;

  template <typename T2> static pack_type set(T2 value) { return value; }
  static pack_type load(const value_type *ptr, size_t index) {
    return ptr[index];
  }
  static pack_type store(value_type *ptr, size_t index, pack_type val) {
    ptr[index] = val;
    return val;
  }
  static pack_type stream(value_type *ptr, size_t index, pack_type val) {
    ptr[index] = val;
    return val;
  }

  template <typename T2, typename tag> struct binary_op {};

  template <typename T2> struct binary_op<T2, add_op> {
    T2 operator()(T2 a, T2 b) { return a + b; }
  };

  template <typename T2> struct binary_op<T2, sub_op> {
    T2 operator()(T2 a, T2 b) { return a - b; }
  };

  template <class tag> static pack_type binary(pack_type a, pack_type b) {
    return binary_op<pack_type, tag>()(a, b);
  }
};

template <typename T> struct vector_inst_set : public scalar_inst_set<T> {};

#if defined(__AVX__)
template <> struct vector_inst_set<float> {
  using value_type = float;
  using pack_type = __m256;
  static const size_t pack_size = 8;
  static const size_t alignment = 32;
  static const size_t registers = 16;

  template <typename T2> static pack_type set(T2 value) {
    return _mm256_set1_ps(value);
  }

  static pack_type load(const value_type *ptr, size_t index) {
    return _mm256_load_ps(ptr + index);
  }

  static pack_type store(value_type *ptr, size_t index, pack_type val) {
    _mm256_store_ps(ptr + index, val);
    return val;
  }
  static pack_type stream(value_type *ptr, size_t index, pack_type val) {
    _mm256_stream_ps(ptr + index, val);
    return val;
  }

  template <typename T2, typename tag> struct binary_op {};

  template <typename T2> struct binary_op<T2, add_op> {
    T2 operator()(T2 a, T2 b) { return _mm256_add_ps(a, b); }
  };

  template <typename T2> struct binary_op<T2, sub_op> {
    T2 operator()(T2 a, T2 b) { return _mm256_sub_ps(a, b); }
  };

  template <class tag> static pack_type binary(pack_type a, pack_type b) {
    return binary_op<pack_type, tag>()(a, b);
  }
};

template <> struct vector_inst_set<double> {
  using value_type = double;
  using pack_type = __m256d;
  static const size_t pack_size = 4;
  static const size_t alignment = 32;
  static const size_t registers = 16;

  template <typename T2> static pack_type set(T2 value) {
    return _mm256_set1_pd(value);
  }
  static pack_type load(const value_type *ptr, size_t index) {
    return _mm256_load_pd(ptr + index);
  }
  static pack_type store(value_type *ptr, size_t index, pack_type val) {
    _mm256_store_pd(ptr + index, val);
    return val;
  }
  static pack_type stream(value_type *ptr, size_t index, pack_type val) {
    _mm256_stream_pd(ptr + index, val);
    return val;
  }

  template <typename T2, typename tag> struct binary_op {};

  template <typename T2> struct binary_op<T2, add_op> {
    T2 operator()(T2 a, T2 b) { return _mm256_add_pd(a, b); }
  };

  template <typename T2> struct binary_op<T2, sub_op> {
    T2 operator()(T2 a, T2 b) { return _mm256_sub_pd(a, b); }
  };

  template <class tag> static pack_type binary(pack_type a, pack_type b) {
    return binary_op<pack_type, tag>()(a, b);
  }
};
#elif defined(__SSE2__)
template <> struct vector_inst_set<float> {
  using value_type = float;
  using pack_type = __m128;
  static const size_t pack_size = 4;
  static const size_t alignment = 16;
  static const size_t registers = 8;

  template <typename T2> static pack_type set(T2 value) {
    return _mm_set1_ps(value);
  }
  static pack_type load(const value_type *ptr, size_t index) {
    return _mm_load_ps(ptr + index);
  }
  static pack_type store(value_type *ptr, size_t index, pack_type val) {
    _mm_store_ps(ptr + index, val);
    return val;
  }
  static pack_type stream(value_type *ptr, size_t index, pack_type val) {
    _mm_stream_ps(ptr + index, val);
    return val;
  }

  template <typename T2, typename tag> struct binary_op {};

  template <typename T2> struct binary_op<T2, add_op> {
    T2 operator()(T2 a, T2 b) { return _mm_add_ps(a, b); }
  };

  template <typename T2> struct binary_op<T2, sub_op> {
    T2 operator()(T2 a, T2 b) { return _mm_sub_ps(a, b); }
  };

  template <class tag> static pack_type binary(pack_type a, pack_type b) {
    return binary_op<pack_type, tag>()(a, b);
  }
};

template <> struct vector_inst_set<double> {
  using value_type = double;
  using pack_type = __m128d;
  static const size_t pack_size = 2;
  static const size_t alignment = 16;
  static const size_t registers = 8;

  template <typename T2> static pack_type set(T2 value) {
    return _mm_set1_pd(value);
  }
  static pack_type load(const value_type *ptr, size_t index) {
    return _mm_load_pd(ptr + index);
  }
  static pack_type store(value_type *ptr, size_t index, pack_type val) {
    _mm_store_pd(ptr + index, val);
    return val;
  }
  static pack_type stream(value_type *ptr, size_t index, pack_type val) {
    _mm_stream_pd(ptr + index, val);
    return val;
  }

  template <typename T2, typename tag> struct binary_op {};

  template <typename T2> struct binary_op<T2, add_op> {
    T2 operator()(T2 a, T2 b) { return _mm_add_pd(a, b); }
  };

  template <typename T2> struct binary_op<T2, sub_op> {
    T2 operator()(T2 a, T2 b) { return _mm_sub_pd(a, b); }
  };

  template <class tag> static pack_type binary(pack_type a, pack_type b) {
    return binary_op<pack_type, tag>()(a, b);
  }
};
#endif // __AVX__

#endif // _SIMD_VECTORIZER_H_
