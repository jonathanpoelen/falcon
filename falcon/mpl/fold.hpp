#ifndef FALCON_MPL_FOLD_HPP
#define FALCON_MPL_FOLD_HPP

#include <falcon/mpl/aux_/fold_impl.hpp>
#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/begin_end.hpp>

namespace falcon {
namespace mpl {

template<
  typename Sequence
, typename State
, typename ForwardOp
>
struct fold
{
  using type = typename aux::fold_impl<deref_t, begin_t<Sequence>, end_t<Sequence>, State, ForwardOp>::type;
};

template<
  typename Sequence
, typename State
, typename ForwardOp
>
using fold_t = typename fold<Sequence, State, ForwardOp>::type;

}
}

#endif
