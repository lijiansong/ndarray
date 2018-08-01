#ifndef INDICES_MAPPER_H
#define INDICES_MAPPER_H

#include "third_party/meta/nano.hpp"

#include <type_traits>
#include <utility>
#include <numeric>

namespace ndarray {
    
// Template parameters:
//  - DT = data type
//  - IF = index of first dimension
//  - IR = index of rest dimensions

namespace detail {

// Indices mapper for static NDArray
template <typename DimSizes, typename... Indices>
struct MapToIndexStatic;

#if 0
// Outer dim to inner dim unroll
template <typename DimSizes, typename IF, typename... IR>
struct MapToIndexStatic<DimSizes, IF, IR...> {
    using end_index = typename std::conditional<
                        DimSizes::size - sizeof...(IR) == 1,
                        typename nano::size_t<0>,
                        typename nano::size_t<DimSizes::size - sizeof...(IR) - 2>>::type;
    
    static constexpr size_t dim_product_sum = nano::accumulate<DimSizes, 0, end_index::value, 1>::result;
    
    static constexpr size_t offset(size_t current_offset, IF&& indice_first, IR&&... indices_rest) {
        return DimSizes::size - sizeof...(IR) == 1
             ? MapToIndexStatic<DimSizes, IR...>::offset(current_offset + indice_first,
                                                         std::forward<IR>(indices_rest)...) 
             : MapToIndexStatic<DimSizes, IR...>::offset(current_offset + indice_first * dim_product_sum,
                                                         std::forward<IR>(indices_rest)...);
    }
};
#endif

// Inner dim to outer dim unroll
template <typename DimSizes, typename IF, typename... IR>
struct MapToIndexStatic<DimSizes, IF, IR...> {
    using start_index = typename std::conditional<
                        DimSizes::size - sizeof...(IR) == DimSizes::size,
                        typename nano::size_t<DimSizes::size - 1>,
                        typename nano::size_t<DimSizes::size - sizeof...(IR)>>::type;
    
    static constexpr size_t dim_product_sum = nano::accumulate<DimSizes, start_index::value, DimSizes::size - 1, 1>::result;

    static constexpr size_t offset(size_t current_offset, IF&& indice_first, IR&&... indices_rest) {
        return DimSizes::size - sizeof...(IR) == DimSizes::size
             ? MapToIndexStatic<DimSizes, IR...>::offset(current_offset + indice_first,
                                                         std::forward<IR>(indices_rest)...) 
             : MapToIndexStatic<DimSizes, IR...>::offset(current_offset + indice_first * dim_product_sum,
                                                         std::forward<IR>(indices_rest)...);
    }
};

// Terminate case
template <typename DimSizes>
struct MapToIndexStatic<DimSizes> {
    static constexpr size_t offset(size_t current_offset) { return current_offset; }
};

// Indices mapper for dynamic NDArray
// Terminate case
template<size_t Iter, typename DimContainer>
size_t MapToIndexDynamic(const DimContainer& dim_sizes, size_t current_offset) {
    return current_offset;
}

#if 0
// Outer dim to inner dim unroll
template<size_t Iter, typename DimContainer, typename IF, typename... IR>
size_t MapToIndexDynamic(const DimContainer& dim_sizes, size_t current_offset, IF indice_first, IR... indices_rest) {
    current_offset += std::accumulate(dim_sizes.begin(),
            dim_sizes.end() - sizeof...(IR) - 1,
            1, std::multiplies<size_t>()) * indice_first;
    return MapToIndexDynamic<Iter + 1>(dim_sizes, current_offset, indices_rest...);
}
#endif

// Inner dim to outer dim unroll
template<size_t Iter, typename DimContainer, typename IF, typename... IR>
size_t MapToIndexDynamic(const DimContainer& dim_sizes, size_t current_offset, IF indice_first, IR... indices_rest) {
    current_offset += std::accumulate(dim_sizes.begin() + dim_sizes.size() - sizeof...(IR),
            dim_sizes.end(),
            1, std::multiplies<size_t>()) * indice_first;
    return MapToIndexDynamic<Iter + 1>(dim_sizes, current_offset, indices_rest...);
}

} // end of namespace detail

struct StaticIndexMapper {

template <typename DimSizes, typename IF, typename... IR>
static constexpr size_t indices_to_index(IF&& indice_first, IR&&... indices_rest) {
    return detail::MapToIndexStatic<DimSizes, IF, IR...>::offset(0,
                                                                 std::forward<IF>(indice_first),
                                                                 std::forward<IR>(indices_rest)... );
}

};

struct DynamicIndexMapper {

template <typename DimContainer, typename IF, typename... IR>
static size_t indices_to_index(const DimContainer& dim_sizes, IF indice_first, IR... indices_rest) {
    return detail::MapToIndexDynamic<0>(dim_sizes, 0, indice_first, indices_rest...);
}

};

} // end of namespace ndarray
#endif // INDICES_MAPPER_H
