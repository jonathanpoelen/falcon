#ifndef FALCON_TUPLE_BUILD_TUPLE_POINTER_HPP
#define FALCON_TUPLE_BUILD_TUPLE_POINTER_HPP

#include <falcon/parameter/pack_pointer.hpp>
#include <falcon/tuple/parameter_pack.hpp>

namespace falcon {

template<typename T, typename Indexes>
struct build_tuple_pointer
{
  typedef typename parameter_pack_to_tuple<
    typename pack_pointer<
      typename tuple_to_parameter_pack_with_parameter_index<T, Indexes>::type
    >::type
  >::type type;
};

template<typename T, typename Indexes>
struct build_tuple_const_pointer
{
  typedef typename parameter_pack_to_tuple<
    typename pack_const_pointer<
      typename tuple_to_parameter_pack_with_parameter_index<T, Indexes>::type
    >::type
  >::type type;
};

template <typename T, typename Indexes>
using build_tuple_pointer_t = typename build_tuple_pointer<T, Indexes>::type;

template <typename T, typename Indexes>
using build_tuple_const_pointer_t = typename build_tuple_const_pointer<T, Indexes>::type;

}

#endif
