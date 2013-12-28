#ifndef FALCON_MPL_COPY_HPP
#define FALCON_MPL_COPY_HPP

#include <falcon/mpl/fold.hpp>

namespace falcon {
namespace mpl {

namespace aux {
  class unspecified_in_cpy;
}

/// TODO if map/set ?
template<typename Sequence, typename In = aux::unspecified_in_cpy>
struct copy
{
  using type = typename fold<
    Sequence
  , typename In::state
  , typename In::operation
  >::type;
};


template<typename Sequence>
struct copy<Sequence, aux::unspecified_in_cpy>
{
  using type = Sequence;
};

template<typename Sequence, typename In = aux::unspecified_in_cpy>
using copy_t = typename copy<Sequence, In>::type;

}
}

#endif
