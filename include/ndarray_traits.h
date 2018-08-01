#ifndef NDARRAY_TRAITS_H
#define NDARRAY_TRAITS_H

#include "ndarray_container.h"

namespace ndarray {

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

// Static container
template <typename DT, size_t... DimSizes>
struct NDArrayTraits;

template <typename DT, size_t SF, size_t... SR>
struct NDArrayTraits<DT, SF, SR...> {
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type = DT;
    using container_type = NDArrayContainer<DT, SF, SR...>;
    using data_container = typename container_type::data_container;
    using dim_container = typename container_type::dim_container;
    using size_type = typename container_type::size_type;
    // ------------------------------------------------------------------------------------------------------
};

// Dynamic container
template <typename DT>
struct NDArrayTraits<DT> {
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type = DT;
    using container_type = NDArrayContainer<DT>;
    using data_container = typename container_type::data_container;
    using dim_container = typename container_type::dim_container;
    using size_type = typename container_type::size_type;
    // ------------------------------------------------------------------------------------------------------
};

} // end of namespace ndarray

#endif // NDARRAY_TRAITS_H
