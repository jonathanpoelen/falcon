#ifndef FALCON_TUPLE_BUILD_TUPLE_REFERENCE_HPP
#define FALCON_TUPLE_BUILD_TUPLE_REFERENCE_HPP

#include <falcon/parameter/pack_reference.hpp>
#include <falcon/tuple/parameter_pack.hpp>

namespace falcon {

template<typename T, typename Indexes>
struct build_tuple_reference
{
  typedef typename parameter_pack_to_tuple<
    typename pack_reference<
      typename tuple_to_parameter_pack_with_parameter_index<T, Indexes>::type
    >::type
  >::type type;
};

template<typename T, typename Indexes>
struct build_tuple_const_reference
{
  typedef typename parameter_pack_to_tuple<
    typename pack_const_reference<
      typename tuple_to_parameter_pack_with_parameter_index<T, Indexes>::type
    >::type
  >::type type;
};

template <typename T, typename Indexes>
using build_tuple_reference_t = typename build_tuple_reference<T, Indexes>::type;

template <typename T, typename Indexes>
using build_tuple_const_reference_t = typename build_tuple_const_reference<T, Indexes>::type;

}

#endif
