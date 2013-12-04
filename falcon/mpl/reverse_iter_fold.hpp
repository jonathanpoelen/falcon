#ifndef FALCON_MPL_REVERSE_ITER_FOLD_HPP
#define FALCON_MPL_REVERSE_ITER_FOLD_HPP

#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/aux_/reverse_fold_impl.hpp>
#include <falcon/type_traits/wrap.hpp>

namespace falcon {
namespace mpl {

template<
  typename Sequence
, typename State
, typename BackwardOp
, typename ForwardOp = arg<1>
>
struct reverse_iter_fold
{
  using type = typename aux::reverse_fold_impl<
    wrap_t
  , begin_t<Sequence>
  , end_t<Sequence>
  , State
  , BackwardOp
  , ForwardOp
  >::type;
};

template<
  typename Sequence
, typename State
, typename BackwardOp
, typename ForwardOp = arg<1>
>
using reverse_iter_fold_t = typename reverse_iter_fold<Sequence, State, BackwardOp, ForwardOp>::type;

}
}

#endif
