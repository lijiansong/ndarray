#ifndef NDARRAY_STATIC_H
#define NDARRAY_STATIC_H

#include "indices_mapper.h"
#include "ndarray_expr_static.h"

#include <random>
#include <ostream>
#include <type_traits>

namespace ndarray {

template <typename Traits>
class NDArrayInterface;

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

template <typename DT, size_t SF, size_t... SR>
using StaticNDArray = NDArrayInterface<NDArrayTraits<DT, SF, SR...>>;

template <typename DT, size_t SF, size_t... SR>
class NDArrayInterface<NDArrayTraits<DT, SF, SR...>> : public NDArrayExpr<StaticNDArray<DT, SF, SR...>, NDArrayTraits<DT, SF, SR...>> {

public:
    // ---------------------------------------- ALIAS'S ----------------------------------------------------- 
    using traits = NDArrayTraits<DT, SF, SR...>;
    using size_type = typename traits::size_type;
    using data_type = typename traits::data_type;
    using container_type = typename traits::container_type;
    using data_container = typename container_type::data_container;
    using dim_container = typename container_type::dim_container;
    // ------------------------------------------------------------------------------------------------------
    
    NDArrayInterface();
    
    NDArrayInterface(data_container& data);
   
    template <typename... TR>
    NDArrayInterface(DT&& first_value, TR&&... other_values);

    template <typename Expression, typename Traits>
    NDArrayInterface(const NDArrayExpr<Expression, Traits>& expression);
    
    constexpr size_type rank() const { return sizeof...(SR) + 1; }
    
    constexpr size_type size() const { return _data.size(); }
 
    inline size_type dim_size(const size_type dim_index) const { return dim_index < rank() ? _dim_sizes[dim_index] : 0; }
    
    constexpr const dim_container& dim_sizes() const { return _dim_sizes; }
    
    void initialize(const data_type min, const data_type max);
    
    inline data_type& operator[](size_type i) { return _data[i]; }
   
    inline const data_type& operator[](size_type i) const { return _data[i]; }
   
    template <typename IF, typename... IR>
    DT& operator()(IF index_dim_one, IR... index_dim_other);
   
    template <typename IF, typename... IR>
    DT operator()(IF index_dim_one, IR... index_dim_other) const;

    DT sum();

    DT max();

    DT min();

    template <size_t FD, size_t... RD>
    StaticNDArray<DT, FD, RD...> reshape();
    // TODO: add slice and local reduce operations

private:
    data_container _data; // Data container which holds all the data
    dim_container _dim_sizes; // Sizes of the dimensions
};

// ----------------------------------------------- IMPL -----------------------------------------------------

template <typename DT, size_t SF, size_t...SR>
NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::NDArrayInterface() {
    // Convert the nano::list of dimension sizes to a constant array
     _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();
};

template <typename DT, size_t SF, size_t...SR>
NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::NDArrayInterface(data_container& data) : _data(data) {
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();
}

template <typename DT, size_t SF, size_t...SR> template <typename... TR> 
NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::NDArrayInterface(DT&& first_value, TR&&... other_values)
: _data{{std::forward<DT>(first_value), std::forward<TR>(other_values)...}} {
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();
}

template <typename DT, size_t SF, size_t...SR> template <typename E, typename T> 
NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::NDArrayInterface(const NDArrayExpr<E, T>& expression) {
    // Convert the nano::list of dimension sizes to a constant array
    _dim_sizes = nano::runtime_converter<typename container_type::dimension_sizes>::to_array();
    for (size_type i = 0; i != size(); ++i) _data[i] = expression[i];
}

template <typename DT, size_t SF, size_t... SR>
void NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::initialize(const data_type min, const data_type max) {
    std::random_device rand_device;
    std::mt19937 gen(rand_device());
    std::uniform_real_distribution<> dist(min, max);
    for (auto& element : _data) element = static_cast<data_type>(dist(gen));
}

template <typename DT, size_t SF, size_t...SR> template <typename IF, typename... IR>
DT& NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::operator()(IF dim_one_index, IR... other_dim_indices) {
    using dimension_sizes = typename container_type::dimension_sizes;
    return _data[StaticMapper::indices_to_index<dimension_sizes>(dim_one_index, other_dim_indices...)];
}

template <typename DT, size_t SF, size_t...SR> template <typename IF, typename... IR>
DT NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::operator()(IF dim_one_index, IR... other_dim_indices) const {
    using dimension_sizes = typename container_type::dimension_sizes;
    return _data[StaticMapper::indices_to_index<dimension_sizes>(dim_one_index, other_dim_indices...)];
}

template <typename DT, size_t SF, size_t... SR>
DT NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::sum() {
    DT sum = static_cast<DT>(0);
    for(auto &&it : _data) {
        sum += it;
    }
    return sum;
}

template <typename DT, size_t SF, size_t... SR>
DT NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::max() {
    DT max = _data[0];
    for(auto &&it : _data) {
        max = max > it ? max : it;
    }
    return max;
}

template <typename DT, size_t SF, size_t... SR>
DT NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::min() {
    DT min = _data[0];
    for(auto &&it : _data) {
        min = min < it ? min : it;
    }
    return min;
}

template <typename DT, size_t SF, size_t... SR> template <size_t FD, size_t... RD>
StaticNDArray<DT, FD, RD...> NDArrayInterface<NDArrayTraits<DT, SF, SR...>>::reshape() {
    using dim_sizes = nano::list<nano::size_t<FD>, nano::size_t<RD>...>;
    using dim_product = nano::multiplies<dim_sizes>;
    static_assert(dim_product::result == container_type::dimension_product::result, "Error! Reshape must have same dimension product!");
    return StaticNDArray<DT, FD, RD...>(_data);
    //tmp._dim_sizes = nano::runtime_converter<dim_sizes>::to_array();
}

// TODO: recursive to dump it like numpy.
template <typename DT, size_t SF, size_t... SR>
std::ostream& operator << (std::ostream& os, const NDArrayInterface<NDArrayTraits<DT, SF, SR...>> &Array) {
    size_t total_size = Array.size();
    size_t last_dim = Array.dim_size(sizeof...(SR));
    for(size_t i = 0; i < total_size/last_dim; ++i) {
        for(size_t j = 0; j < last_dim; ++j) {
            if(j == last_dim - 1) {
                os << Array[i * last_dim + j] << '\n';
            } else {
                os << Array[i * last_dim + j] << ",\t";
            }
        }
    }
    return os;
}

} // end of namespace ndarray

#endif // NDARRAY_STATIC_H
