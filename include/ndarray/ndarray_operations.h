#ifndef NDARRAY_OPERATIONS_H
#define NDARRAY_OPERATIONS_H

#include "ndarray_add.h"
#include "ndarray_sub.h"
#include "ndarray_mul.h"

namespace {

template <typename E1, typename E2, typename T1, typename T2>
const ndarray::NDArrayAddition<E1, E2, T1, T2> operator + (ndarray::NDArrayExpr<E1, T1> const& x, ndarray::NDArrayExpr<E2, T2> const& y) {
    return ndarray::NDArrayAddition<E1, E2, T1, T2>(x, y);
}

template <typename E1, typename E2, typename T1, typename T2>
const ndarray::NDArraySubtraction<E1, E2, T1, T2> operator - (ndarray::NDArrayExpr<E1, T1> const& x, ndarray::NDArrayExpr<E2, T2> const& y) {
    return ndarray::NDArraySubtraction<E1, E2, T1, T2>(x, y);
}

template <typename E1, typename E2, typename T1, typename T2>
const ndarray::NDArrayMultiplication<E1, E2, T1, T2> operator * (ndarray::NDArrayExpr<E1, T1> const& x, ndarray::NDArrayExpr<E2, T2> const& y) {
    return ndarray::NDArrayMultiplication<E1, E2, T1, T2>(x, y);
}

} // end of anonymous namespace

#endif // NDARRAY_OPERATIONS_H
