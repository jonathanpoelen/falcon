#ifndef FALCON_MPL_ITER_FOLD_HPP
#define FALCON_MPL_ITER_FOLD_HPP

#include <falcon/mpl/aux_/fold_impl.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/type_traits/wrap.hpp>

namespace falcon {
namespace mpl {

template<
  typename Sequence
, typename State
, typename ForwardOp
>
struct iter_fold
{
  using type = typename aux::fold_impl<wrap_t, begin_t<Sequence>, end_t<Sequence>, State, ForwardOp>::type;
};

template<
  typename Sequence
, typename State
, typename ForwardOp
>
using iter_fold_t = typename fold<Sequence, State, ForwardOp>::type;

}
}

#endif
