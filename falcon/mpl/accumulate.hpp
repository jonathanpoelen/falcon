#ifndef FALCON_MPL_ACCUMULATE_HPP
#define FALCON_MPL_ACCUMULATE_HPP

#include <falcon/mpl/fold.hpp>

namespace falcon {
namespace mpl {

template<
  typename Sequence
, typename State
, typename ForwardOp
>
using accumulate = fold<Sequence, State, ForwardOp>;

template<
  typename Sequence
, typename State
, typename ForwardOp
>
using accumulate_t = typename fold<Sequence, State, ForwardOp>::type;

}
}

#endif
