#ifndef NDARRAY_H
#define NDARRAY_H

#include "ndarray_static.h"
#include "ndarray_dynamic.h"
#include "ndarray_operations.h"

namespace ndarray {

// Wrapper for static and dynamic NDArray
template <typename Dtype, size_t... DimSizes>
using NDArray = NDArrayInterface<NDArrayTraits<Dtype, DimSizes...>>;

} // end of namespace ndarray

#endif // NDARRAY_H
