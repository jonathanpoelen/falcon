#ifndef FALCON_MPL_AUX__FOLD_IMPL_HPP
#define FALCON_MPL_AUX__FOLD_IMPL_HPP

#include <falcon/mpl/next.hpp>
#include <falcon/mpl/apply.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<
  template<class> class Deref
, typename Begin
, typename Last
, typename State
, typename ForwardOp
>
struct fold_impl
: fold_impl<
  Deref
, next_t<Begin>
, Last
, apply_t<ForwardOp, State, Deref<Begin>>
, ForwardOp
>
{};

template<
  template<class> class Deref
, typename Last
, typename State
, typename ForwardOp
>
struct fold_impl<Deref, Last, Last, State, ForwardOp>
{ using type = State; };

}
}
}

#endif
