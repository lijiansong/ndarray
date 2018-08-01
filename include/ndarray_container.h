#ifndef NDARRAY_CONTAINER_H
#define NDARRAY_CONTAINER_H

#include "third_party/meta/nano.hpp"
#include <array>

namespace ndarray {

template <typename DT, size_t... Sizes>
class NDArrayContainer;

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

// static container
template <typename DT, std::size_t SF, std::size_t... SR>
class NDArrayContainer<DT, SF, SR...> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type = DT;
    using dimension_sizes = nano::list<nano::size_t<SF>, nano::size_t<SR>...>;
    using dimension_product = nano::multiplies<dimension_sizes>;
    using data_container = std::array<data_type, dimension_product::result>;
    using dim_container = typename nano::runtime_converter<dimension_sizes>::array_type;
    using size_type = typename data_container::size_type;
    using iterator = typename data_container::iterator;
    // ------------------------------------------------------------------------------------------------------

    NDArrayContainer() {}

    constexpr NDArrayContainer(data_container& data) : _data(data) {}

    template <typename... TR> 
    constexpr NDArrayContainer(TR&&... values) : _data{{std::forward<TR>(values)...}} {}

    constexpr std::size_t size() const { return dimension_product::result; }
    
    inline data_type& operator[](std::size_t i) { return _data[i]; }

    inline const data_type& operator[](std::size_t i) const { return _data[i]; }

    iterator begin() { return _data.begin(); }

    iterator end() { return _data.end(); }

private:
    data_container _data;
};

// dynamic container
template <typename DT>
class NDArrayContainer<DT> {
public:
    // ---------------------------------------- ALIAS'S -----------------------------------------------------
    using data_type = DT;
    using data_container = std::vector<data_type>;
    using size_type = typename data_container::size_type;
    using dim_container = std::vector<size_type>;
    using iterator = typename data_container::iterator;
    // ------------------------------------------------------------------------------------------------------

    NDArrayContainer() : _size(0), _data(0) {}

    NDArrayContainer(data_container& data) : _size(data.size()), _data(data){}

    inline std::size_t size() const { return _size; }

    inline data_type& operator[](std::size_t i) { return _data[i]; }

    inline const data_type& operator[](std::size_t i) const { return _data[i]; }

    iterator begin() { return _data.begin(); }

    iterator end() { return _data.end(); }

private:
    data_container _data;
    std::size_t _size;
};

} // end of namespace ndarray

#endif // NDARRAY_CONTAINER_H
