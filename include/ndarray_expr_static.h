#ifndef NDARRAY_EXPR_STATIC_H
#define NDARRAY_EXPR_STATIC_H

#include "ndarray_expr_interface.h"

namespace ndarray {

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

template <typename Expr, typename DT, size_t SF, size_t... SR>
class NDArrayExpr<Expr, NDArrayTraits<DT, SF, SR...>> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using traits = NDArrayTraits<DT, SF, SR...>;
    using size_type = typename traits::size_type;
    using data_type = typename traits::data_type;
    using container_type = typename traits::container_type;
    using data_container = typename traits::data_container;
    using dim_container = typename traits::dim_container;
    // ------------------------------------------------------------------------------------------------------ 
    
    Expr* expr() { return static_cast<Expr*>(this); }

    const Expr* expr() const { return static_cast<const Expr*>(this); }    

    operator Expr&() { return static_cast<Expr&>(*this); }

    operator Expr const&() const { return static_cast<const Expr&>(*this); }

    constexpr size_type size() const { return expr()->size(); }

    constexpr size_type rank() const { return expr()->rank(); }

    constexpr const dim_container& dim_sizes() const { return expr()->dim_sizes(); }

    inline data_type& operator[](size_type i) { return expr()->operator[](i); }

    inline const data_type& operator[](size_type i) const { return expr()->operator[](i); }

    template <typename IF, typename... IR>
    DT operator()(IF dim_index_first, IR... dim_index_rest) {
        using dimension_sizes = typename container_type::dimension_sizes;
        return expr()->operator[](StaticIndexMapper::indices_to_index<dimension_sizes>(dim_index_first, dim_index_rest...));
    }

    template <typename IF, typename... IR>
    DT operator()(IF dim_index_first, IR... dim_index_rest) const {
        using dimension_sizes = typename container_type::dimension_sizes;
        return expr()->operator[](StaticIndexMapper::indices_to_index<dimension_sizes>(dim_index_first, dim_index_rest...));
    }
};
            
} // end of namespace ndarray

#endif // NDARRAY_EXPR_STATIC_H
