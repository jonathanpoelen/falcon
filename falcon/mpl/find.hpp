#ifndef FALCON_MPL_FIND_HPP
#define FALCON_MPL_FIND_HPP

#include <falcon/mpl/aux_/find_impl.hpp>
#include <falcon/mpl/begin_end.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T>
struct find
{
  using type = typename aux::find_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , T
  >::type;
};

template<typename Sequence, typename T>
using find_t = typename find<Sequence, T>::type;

}
}

#endif
