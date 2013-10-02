#ifndef FALCON_TUPLE_TUPLE_MODIFIER_HPP
#define FALCON_TUPLE_TUPLE_MODIFIER_HPP

#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/parameter/manip.hpp>

namespace falcon {

template <template<class...> class Modifier, typename Tuple,
  typename Indexes = typename build_parameter_index<
    std::tuple_size<Tuple>::value
  >::type
>
struct tuple_modifier
{
  typedef typename parameter_pack_to_tuple<
    typename parameter::modifier<
      Modifier,
      typename tuple_to_parameter_pack_with_parameter_index<
        Tuple, Indexes
      >::type
    >::type
  >::type type;
};

}

#endif
