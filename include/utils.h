#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#define VECTOR_ALIGN(alignment) __attribute__((aligned(alignment)))
#define LOG()                                                                  \
  {                                                                            \
    std::cout << __PRETTY_FUNCTION__ << "in file " << __FILE__ << ":"          \
              << __LINE__ << '\n';                                             \
  }

namespace utils {

// tuple
template <typename f, typename... r> struct tuple : public tuple<r...> {
  tuple(f _f, r... _r) : tuple<r...>(_r...), _f(_f) {}
  f _f;
};

template <typename f> struct tuple<f> {
  tuple(f _f) : _f(_f) {}
  f _f;
};

template <int i, typename f, typename... r> struct get_impl {
  static auto value(const tuple<f, r...> *t)
      -> decltype(get_impl<i - 1, r...>::value(t)) {
    return get_impl<i - 1, r...>::value(t);
  }
};

template <typename f, typename... r> struct get_impl<0, f, r...> {
  static f value(const tuple<f, r...> *t) { return t->_f; }
};

template <int i, typename f, typename... r>
auto get(const tuple<f, r...> &t) -> decltype(get_impl<i, f, r...>::value(&t)) {
  return get_impl<i, f, r...>::value(&t);
}

} // end of namespace utils

#endif // _UTILS_H_
