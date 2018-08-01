#ifndef NDARRAY_ADD_H
#define NDARRAY_ADD_H

#include "ndarray_expr_static.h"
#include "ndarray_expr_dynamic.h"

namespace ndarray {

template <typename E1, typename E2, typename T1, typename T2>
class NDArrayAdd : public NDArrayExpr<NDArrayAdd<E1, E2, T1, T2>, T1> {
public:
    using traits = T1;
    using dim_container = typename traits::dim_container;
    using size_type = typename traits::size_type;
    using data_type = typename traits::data_type;
private:
    E1 const& _x; // First expression for addition
    E2 const& _y; // Second expression for addition
public:

    NDArrayAdd(NDArrayExpr<E1, T1> const& x, NDArrayExpr<E2, T2> const& y); 

    inline const dim_container& dim_sizes() const { return _x.dim_sizes(); }
    
    inline const size_type size() const { return _x.size(); }

    inline const size_type rank() const { return _x.rank(); }
    
    inline data_type operator[](size_type i) const { return _x[i] + _y[i]; }
};  

template <typename E1, typename E2, typename T1, typename T2>
NDArrayAdd<E1, E2, T1, T2>::NDArrayAdd(const NDArrayExpr<E1, T1>& x,
                                               const NDArrayExpr<E2, T2>& y)
: _x(x), _y(y) {
    // FIXME: checking
}

} // end of namespace ndarray  

#endif // NDARRAY_ADD_H
