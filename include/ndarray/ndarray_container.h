#ifndef NDARRAY_CONTAINER_H
#define NDARRAY_CONTAINER_H

#include "meta/nano.hpp"
#include <array>

namespace ndarray {

template <typename DT, size_t... Sizes>
class NDArrayContainer;

// Template parameters:
//  - DT = data type
//  - SF = size of first dimension
//  - SR = size of other dimensions

// static containers
template <typename DT, size_t SF, size_t... SR>
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

    constexpr size_t size() const { return dimension_product::result; }
    
    inline data_type& operator[](size_t i) { return _data[i]; }

    inline const data_type& operator[](size_t i) const { return _data[i]; }

    iterator begin() { return _data.begin(); }

    iterator end() { return _data.end(); }
private:
    data_container _data;
};

} // end of namespace ndarray

#endif // NDARRAY_CONTAINER_H
