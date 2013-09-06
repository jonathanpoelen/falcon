#ifndef FALCON_TUPLE_PARAMETER_INDEX_HPP
#define FALCON_TUPLE_PARAMETER_INDEX_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <type_traits>

namespace falcon {

template <typename T>
struct build_tuple_index
{
  typedef typename build_parameter_index<
    std::tuple_size<
      typename std::decay<T>::type
    >::value
  >::type type;
};

template <typename T>
using build_tuple_index_t = typename build_tuple_index<T>::type;

}

#endif
