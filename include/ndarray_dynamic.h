#ifndef NDARRAY_DYNAMIC_H
#define NDARRAY_DYNAMIC_H

#include "indices_mapper.h"
#include "ndarray_expr_dynamic.h"

#include <initializer_list>
#include <numeric>

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

namespace ndarray {

template <typename Traits>
class NDArrayInterface;

template <typename DT>
using DynamicNDArray = NDArrayInterface<NDArrayTraits<DT>>;

template <typename DT>
class NDArrayInterface<NDArrayTraits<DT>> : public NDArrayExpr<DynamicNDArray<DT>, NDArrayTraits<DT>> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using traits = NDArrayTraits<DT>;
    using container_type = typename traits::container_type;
    using data_container = typename traits::data_container;
    using dim_container = typename traits::dim_container;
    using data_type = typename traits::data_type;
    using size_type = typename traits::size_type;
    // ------------------------------------------------------------------------------------------------------

    explicit NDArrayInterface(size_type rank) : _data(0), _rank(rank), _dim_sizes(rank) {}

    NDArrayInterface(dim_container& dim_sizes, data_container& data);

    NDArrayInterface(dim_container&& dim_sizes, data_container&& data);

    NDArrayInterface(std::initializer_list<size_type> dim_sizes);

    template <typename Expr, typename Traits>
    NDArrayInterface(const NDArrayExpr<Expr, Traits>& expr);

    inline size_type rank() const { return _rank; }

    inline size_type size() const { return _data.size(); }

    // FIXME: out of range exception
    inline size_t dim_size(const int dim) const { return dim < _rank ? _dim_sizes[dim] : 0; }

    const dim_container& dim_sizes() const { return _dim_sizes; }

    const data_container& data() const { return _data; }

    void initialize(const data_type min, const data_type max);

    inline data_type& operator[](size_type i) { return _data[i]; }

    inline const data_type& operator[](size_type i) const { return _data[i]; }

    template <typename IF, typename... IR>
    DT& operator()(IF dim_index_first, IR... dim_index_rest);

    template <typename IF, typename... IR>
    DT operator()(IF dim_index_first, IR... dim_index_rest) const;

    DT sum();

    DT max();

    DT min();

    template <size_t FD, size_t... RD>
    DynamicNDArray<DT> reshape();

private:
    data_container _data;
    dim_container _dim_sizes;
    size_type _rank;
};

template <typename DT>
NDArrayInterface<NDArrayTraits<DT>>::NDArrayInterface(dim_container& dim_sizes, data_container& data)
: _data(data), _rank(dim_sizes.size()), _dim_sizes(dim_sizes) {
    // TODO: dimension checking
}

template <typename DT>
NDArrayInterface<NDArrayTraits<DT>>::NDArrayInterface(dim_container&& dim_sizes, data_container&& data)
: _data(data), _rank(dim_sizes.size()), _dim_sizes(dim_sizes) {
    // TODO: dimension checking
}

template <typename DT>
NDArrayInterface<NDArrayTraits<DT>>::NDArrayInterface(std::initializer_list<size_type> dim_sizes)
: _data(std::accumulate(dim_sizes.begin(), dim_sizes.end(), 1, std::multiplies<size_type>())),
    _rank(dim_sizes.size()) {
    for (auto& dim : dim_sizes) _dim_sizes.push_back(dim);
}

template <typename DT> template <typename E, typename T>
NDArrayInterface<NDArrayTraits<DT>>::NDArrayInterface(const NDArrayExpr<E, T>& expr)
: _data(expr.size()), _dim_sizes(expr.dim_sizes()), _rank(expr.rank()) {
    for (size_type i = 0; i != size(); ++i) _data[i] = expr[i];
}

template <typename DT>
void NDArrayInterface<NDArrayTraits<DT>>::initialize(const data_type min, const data_type max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    for (auto& elem : _data) elem = static_cast<data_type>(dist(gen));
}

template <typename DT> template <typename IF, typename... IR>
DT& NDArrayInterface<NDArrayTraits<DT>>::operator()(IF dim_index_first, IR... dim_index_rest) {
    return _data[DynamicIndexMapper::indices_to_index(_dim_sizes, dim_index_first, dim_index_rest...)];
}

template <typename DT> template <typename IF, typename... IR>
DT NDArrayInterface<NDArrayTraits<DT>>::operator()(IF dim_index_first, IR... dim_index_rest) const {
    return _data[DynamicIndexMapper::indices_to_index(_dim_sizes, dim_index_first, dim_index_rest...)];
}

template <typename DT>
DT NDArrayInterface<NDArrayTraits<DT>>::sum() {
    DT sum = static_cast<DT>(0);
    for(auto &&it : _data) {
        sum += it;
    }
    return sum;
}

template <typename DT>
DT NDArrayInterface<NDArrayTraits<DT>>::max() {
    DT max = _data[0];
    for(auto &&it : _data) {
        max = max > it ? max : it;
    }
    return max;
}

template <typename DT>
DT NDArrayInterface<NDArrayTraits<DT>>::min() {
    DT min = _data[0];
    for(auto &&it : _data) {
        min = min < it ? min : it;
    }
    return min;
}

template <typename DT> template <size_t FD, size_t... RD>
DynamicNDArray<DT> NDArrayInterface<NDArrayTraits<DT>>::reshape() {
    // TODO: dimension checking
    std::vector<size_type> new_dim{{FD, RD...}};
    return DynamicNDArray<DT>(new_dim, _data);
}

// TODO: recursive to dump it like numpy.
template <typename DT>
std::ostream& operator << (std::ostream& os, const NDArrayInterface<NDArrayTraits<DT>> &Array) {
    size_t total_size = Array.size();
    size_t last_dim = Array.dim_size(Array.dim_sizes().size() - 1);
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
#endif // NDARRAY_DYNAMIC_H
