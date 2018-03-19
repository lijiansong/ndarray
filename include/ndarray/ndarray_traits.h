#ifndef NDARRAY_TRAITS_H
#define NDARRAY_TRAITS_H

#include "ndarray_container.h"

namespace ndarray {

template <typename Dtype, size_t... DimSizes>
struct NDArrayTraits;

template <typename Dtype, size_t SizeFirst, size_t... SizeRest>
struct NDArrayTraits<Dtype, SizeFirst, SizeRest...> {
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type = Dtype;
    using container_type = NDArrayContainer<Dtype, SizeFirst, SizeRest...>;
    using data_container = typename container_type::data_container;
    using dim_container = typename container_type::dim_container;
    using size_type = typename container_type::size_type;
    // ------------------------------------------------------------------------------------------------------
};

} // end of namespace ndarray
#endif // NDARRAY_TRAITS_H
