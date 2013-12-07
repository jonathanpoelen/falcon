#ifndef FALCON_MPL_CONTAINS_HPP
#define FALCON_MPL_CONTAINS_HPP

#include <falcon/mpl/aux_/contains_impl.hpp>
#include <falcon/mpl/begin_end.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T>
struct contains
{
  using type = typename aux::contains_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , T
  >::type;

  const static decltype(type::value) value = type::value;
};

template<typename Sequence, typename T>
using contains_t = typename contains<Sequence, T>::type;


}
}

#endif
