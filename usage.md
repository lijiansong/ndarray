---
layout: page
title: NDArray Usage
---

## 1. NDArray Construction

`Static NDArray` is a template interface, as defined below:
```
template <typename DT, size_t SF, size_t... SR>
using StaticNDArray = NDArrayInterface<NDArrayTraits<DT, SF, SR...>>;
```

There are many ways to construct a static NDArray, its constructors are shown below:

```
// 1. default constructor
NDArrayInterface();

// 2. construct a static NDArray from a std::array
NDArrayInterface(data_container& data);

// 3. initialize list
template <typename... TR>
NDArrayInterface(DT&& first_value, TR&&... other_values);

// 4. construct a static NDArray from NDarray expression
template <typename Expr, typename Traits>
NDArrayInterface(const NDArrayExpr<Expr, Traits>& expr);
```

While to construct a dynamic NDArray, you can use the following constructors:

```
// 1. constructor a dynamic ndarray with a rank 
NDArrayInterface(size_type rank) : _data(0), _rank(rank), _dim_sizes(rank) {}

// 2. construct a dynamic ndarray with a vector of dimension and data
NDArrayInterface(dim_container& dim_sizes, data_container& data);

// 3. construct a dynamic ndarray with an initialize list to specify its dimension info
NDArrayInterface(std::initializer_list<size_type> dim_sizes);

// 4. construct a dynamic NDArray from NDarray expressions
template <typename Expr, typename Traits>
NDArrayInterface(const NDArrayExpr<Expr, Traits>& expr);
```

## 2. NDArray Builtin Functions
NDArray has some builtin fucntions to get the information about the NDArray instance. Both static and dynamic NDArray share the following interfaces.

```
// 1. rank(), get the total dimension of a NDArray
constexpr size_type rank() const;

// 2. size(), get the total number of elements in a NDArray
constexpr size_type size() const;

// 3. dim_sizes(), get the dimension array of a NDArray, for static NDArray it return a std::array, while for dynamic NDArray, it returns a std::vector
constexpr const dim_container& dim_sizes() const;

// 4. dim_size(const size_type), get the size of the given index dimension of a NDarray
inline size_type dim_size(const size_type dim_index) const;

// 5. data(), get the data of a NDArray, for static NDArray, it returns a std::array, while for dynamic NDArray, it returns a std::vector
const data_container& data() const { return _data; }

```

## 3. NDArray Element Access
There are two ways to access a NDArray element, one is by `[]` operator with a index which similar to access an one dimension array, another is by the `(i, j, k, ...)` operator to get the element at the given position.

```
// 1. [], get the i-th element in a NDArray
inline const data_type& operator[](size_type i);

// 2. (i, j, k, ...), get the a NDArray element at the position (i, j, k, ...)
template <typename IF, typename... IR>
DT& operator()(IF index_dim_one, IR... index_dim_other);
```

## 4. NDArray Operations
NDArray supports arithmatic operations, e.g. addition, subtraction, multiplication and etc. Besides, it also supports global reduction, local reduction, slice, reshape and etc.

```
// 1. +, NDArray addition
template <typename E1, typename E2, typename T1, typename T2>
const ndarray::NDArrayAddition<E1, E2, T1, T2> operator + (ndarray::NDArrayExpr<E1, T1> const& x, ndarray::NDArrayExpr<E2, T2> const& y)

// 2. -, NDArray subtraction
template <typename E1, typename E2, typename T1, typename T2>
const ndarray::NDArraySubtraction<E1, E2, T1, T2> operator - (ndarray::NDArrayExpr<E1, T1> const& x, ndarray::NDArrayExpr<E2, T2> const& y)

// 3. *, NDArray multiplication
template <typename E1, typename E2, typename T1, typename T2>
const ndarray::NDArrayMultiplication<E1, E2, T1, T2> operator * (ndarray::NDArrayExpr<E1, T1> const& x, ndarray::NDArrayExpr<E2, T2> const& y)

// 4. global reduction: sum(), get the total sumary of a NDArray
DT sum();

// 5. global reduction: max(), get the maximum value of a NDArray
DT max();

// 6. global reduction: min(), get the minimum value of a NDArray
DT min();

// 7. reshape(), reshape a NDArray with new dimensions
template <size_t FD, size_t... RD>
StaticNDArray<DT, FD, RD...> reshape();
```

More details about the NDArray usage, please checkout NDArray [test cases](https://github.com/lijiansong/ndarray/tree/master/examples).
