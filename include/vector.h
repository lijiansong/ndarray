#ifndef VECTOR_H
#define VECTOR_H

#include "vector_dynamic.h"
#include "vector_static.h"

namespace ndarray {

template <typename T, size_t N> using Vector = VectorInterface<T, N>;
}

#endif // VECTOR_H
