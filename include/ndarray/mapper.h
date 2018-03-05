#ifndef MAPPER_H
#define MAPPER_H

#include "meta/nano.hpp"

#include <type_traits>
#include <utility>
#include <numeric>

namespace ndarray {
    
namespace detail {

template <typename DimSizes, typename... Indices>
struct MapToIndexStatic;

template <typename DimSizes, typename IF, typename... IR>
struct MapToIndexStatic<DimSizes, IF, IR...> {
    // On each iteration the product of the size of all previous dimensions must be calculated
    // to determine the memory offset of this dimension, so determine the stopping index
    using end_index = typename std::conditional<
                        DimSizes::size - sizeof...(IR) == 1,
                        typename nano::size_t<0>,
                        typename nano::size_t<DimSizes::size - sizeof...(IR) - 2>>::type;
    
    // The product sum of the previous dimensions (previous iterations) so if we are on iteration
    // 3 then this is the product of the size of dimension 0 and 1
    static constexpr size_t dim_product_sum = nano::accumulate<DimSizes, 0, end_index::value, 1>::result;
    
    // The offset calculation 
    static constexpr size_t offset(size_t current_offset, IF&& index_first, IR&&... indices_rest) {
        // Recursively call until the terminating case 
        // If first iteration use index_first as offset
        // if other iteration, add mult with prev products
        return DimSizes::size - sizeof...(IR) == 1
             ? MapToIndexStatic<DimSizes, IR...>::offset(current_offset + index_first,
                                                         std::forward<IR>(indices_rest)...) 
             : MapToIndexStatic<DimSizes, IR...>::offset(current_offset + index_first * dim_product_sum,
                                                         std::forward<IR>(indices_rest)...);
    }
};

// Terminating (base) case
template <typename DimSizes>
struct MapToIndexStatic<DimSizes> {
    // Just need to return the result here
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
#endif // MAPPER_H
