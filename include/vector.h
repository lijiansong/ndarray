#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "vector_dynamic.h"
#include "vector_static.h"

namespace ndarray {

template <typename T, size_t N> using Vector = VectorInterface<T, N>;
}

#endif // _VECTOR_H_
