#ifndef NDARRAY_H
#define NDARRAY_H

#include "ndarray_static.h"
#include "ndarray_dynamic.h"
#include "ndarray_operations.h"
#include "vector_static.h"
#include "vector_dynamic.h"

namespace ndarray {

// Wrapper for static and dynamic NDArray
template <typename Dtype, size_t... DimSizes>
using NDArray = NDArrayInterface<NDArrayTraits<Dtype, DimSizes...>>;

// Wrapper for static and dynamic Vector
template <typename T, size_t N> using Vector = VectorInterface<T, N>;

} // end of namespace ndarray

#endif // NDARRAY_H
