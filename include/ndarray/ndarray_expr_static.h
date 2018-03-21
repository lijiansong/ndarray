#ifndef NDARRAY_EXPR_STATIC_H
#define NDARRAY_EXPR_STATIC_H

#include "ndarray_expr_interface.h"

namespace ndarray {

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

template <typename Expression, typename DT, size_t SF, size_t... SR>
class NDArrayExpr<Expression, NDArrayTraits<DT, SF, SR...>> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using traits = NDArrayTraits<DT, SF, SR...>;
    using size_type = typename traits::size_type;
    using data_type = typename traits::data_type;
    using container_type = typename traits::container_type;
    using data_container = typename traits::data_container;
    using dim_container = typename traits::dim_container;
    // ------------------------------------------------------------------------------------------------------ 
    
    Expression* expression() { return static_cast<Expression*>(this); }

    const Expression* expression() const { return static_cast<const Expression*>(this); }    
   
    operator Expression&() { return static_cast<Expression&>(*this); }

    operator Expression const&() const { return static_cast<const Expression&>(*this); }
    
    constexpr size_type size() const { return expression()->size(); }

    constexpr size_type rank() const { return expression()->rank(); }
    
    constexpr const dim_container& dim_sizes() const { return expression()->dim_sizes(); }

    inline data_type& operator[](size_type i) { return expression()->operator[](i); }
    
    inline const data_type& operator[](size_type i) const { return expression()->operator[](i); }
    
    template <typename IF, typename... IR>
    DT operator()(IF index_dim_one, IR... index_dim_other) {
        using dimension_sizes = typename container_type::dimension_sizes;
        return expression()->operator[](StaticMapper::indices_to_index<dimension_sizes>(index_dim_one, index_dim_other...));
    }
   
    template <typename IF, typename... IR>
    DT operator()(IF index_dim_one, IR... index_dim_other) const {
        using dimension_sizes = typename container_type::dimension_sizes;
        return expression()->operator[](StaticMapper::indices_to_index<dimension_sizes>(index_dim_one, index_dim_other...));
    }
};
            
} // end of namespace ndarray

#endif // NDARRAY_EXPR_STATIC_H
