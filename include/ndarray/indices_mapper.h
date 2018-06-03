#ifndef INDICES_MAPPER_H
#define INDICES_MAPPER_H

#include "meta/nano.hpp"

#include <type_traits>
#include <utility>
#include <numeric>

namespace ndarray {
    
namespace detail {

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
    
    static constexpr size_t offset(size_t current_offset, IF&& index_first, IR&&... indices_rest) {
        return DimSizes::size - sizeof...(IR) == 1
             ? MapToIndexStatic<DimSizes, IR...>::offset(current_offset + index_first,
                                                         std::forward<IR>(indices_rest)...) 
             : MapToIndexStatic<DimSizes, IR...>::offset(current_offset + index_first * dim_product_sum,
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
    
    static constexpr size_t offset(size_t current_offset, IF&& index_first, IR&&... indices_rest) {
        return DimSizes::size - sizeof...(IR) == DimSizes::size
             ? MapToIndexStatic<DimSizes, IR...>::offset(current_offset + index_first,
                                                         std::forward<IR>(indices_rest)...) 
             : MapToIndexStatic<DimSizes, IR...>::offset(current_offset + index_first * dim_product_sum,
                                                         std::forward<IR>(indices_rest)...);
    }
};

// Terminate case
template <typename DimSizes>
struct MapToIndexStatic<DimSizes> {
    static constexpr size_t offset(size_t current_offset) { return current_offset; }
};

} // end of namespace detail

struct StaticMapper {

template <typename DimSizes, typename IF, typename... IR>
static constexpr size_t indices_to_index(IF&& index_first, IR&&... indices_rest) {
    return detail::MapToIndexStatic<DimSizes, IF, IR...>::offset(0,
                                                                 std::forward<IF>(index_first),
                                                                 std::forward<IR>(indices_rest)... );
}

};

} // end of namespace ndarray
#endif // INDICES_MAPPER_H
