#ifndef FALCON_MPL_REVERSE_FOLD_HPP
#define FALCON_MPL_REVERSE_FOLD_HPP

#include <falcon/mpl/deref.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/aux_/reverse_fold_impl.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename State, typename BackwardOp, typename ForwardOp = arg<1>>
struct reverse_fold
{
  using type = typename aux::reverse_fold_impl<
    deref_t
  , begin_t<Sequence>
  , end_t<Sequence>
  , State
  , BackwardOp
  , ForwardOp
  >::type;
};

template<typename Sequence, typename State, typename BackwardOp, typename ForwardOp = arg<1>>
using reverse_fold_t = typename reverse_fold<Sequence, State, BackwardOp, ForwardOp>::type;

}
}

#endif
