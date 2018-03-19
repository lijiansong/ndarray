#ifndef NDARRAY_H
#define NDARRAY_H

#include "ndarray_static.h"
#include "ndarray_operations.h"

namespace ndarray {

template <typename Dtype, size_t... DimSizes>
using NDArray = NDArrayInterface<NDArrayTraits<Dtype, DimSizes...>>;

} // end of namespace ndarray

#endif // NDARRAY_INTERFACE_H
