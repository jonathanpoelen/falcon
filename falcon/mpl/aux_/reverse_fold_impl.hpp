#ifndef FALCON_MPL_AUX__REVERSE_FOLD_IMPL_HPP
#define FALCON_MPL_AUX__REVERSE_FOLD_IMPL_HPP

#include <falcon/sfinae/has_type.hpp>

#include <falcon/mpl/if.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/prior.hpp>
#include <falcon/mpl/vector.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/push_front.hpp>

#include <falcon/mpl/aux_/iter.hpp>
#include <falcon/mpl/aux_/fold_impl.hpp>

#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/eval_if.hpp>

#include <type_traits>


namespace falcon {
namespace mpl {
namespace aux {

template<
  template<class> class Deref
, typename Begin
, typename Last
, typename State
, typename BackwardOp
, typename ForwardOp
, typename = void
>
struct dispatch_reverse_fold_impl
{
  template<typename Vec = vector<>, typename St = State>
  struct new_state
  {
    using vec = Vec;
    using state = St;
  };

  template<typename St, typename T>
  struct new_forward_op
  {
    using type = new_state<
      push_front_t<typename St::vec, T>
    >;
  };

  template<typename St, typename T>
  struct new_forward_op2
  {
    using type = new_state<
      push_front_t<typename St::vec, T>
    , apply_t<ForwardOp, typename St::state, T>
    >;
  };

  using state = typename fold_impl<
    Deref
  , Begin
  , Last
  , new_state<>
  , if_t<
      std::is_same<ForwardOp, arg<1>>
    , new_forward_op<arg<1>, arg<2>>
    , new_forward_op2<arg<1>, arg<2>>>
  >::type;

  using type = typename fold_impl<
    Deref
  , begin_t<typename state::vec>
  , end_t<typename state::vec>
  , typename state::state
  , BackwardOp
  >::type;
};

template<
  template<class> class Deref
, typename Begin
, typename Last
, typename State
, typename BackwardOp
, typename ForwardOp
>
struct dispatch_reverse_fold_impl<
  Deref
, Begin
, Last
, State
, BackwardOp
, ForwardOp
, enable_type_t<prior_t<Last>>
>
: fold_impl<
  Deref
, reverse_iterator<prior_t<Last>>
, reverse_iterator<prior_t<Begin>>
, eval_if_c_t<
    std::is_same<ForwardOp, arg<1>>
  , use<State>
  , fold_impl<
      Deref
    , Begin
    , Last
    , State
    , ForwardOp
    >
  >
, BackwardOp
>
{};

template<
  template<class> class Deref
, typename Begin
, typename Last
, typename State
, typename BackwardOp
, typename ForwardOp
>
struct reverse_fold_impl
: dispatch_reverse_fold_impl<
  Deref
, typename forward_iterator_to_bidirectional_iterator<Begin>::type
, typename forward_iterator_to_bidirectional_iterator<Last>::type
, State
, BackwardOp
, ForwardOp
>
{};

template<
  template<class> class Deref
, typename Last
, typename State
, typename BackwardOp
, typename ForwardOp
>
struct reverse_fold_impl<Deref, Last, Last, State, BackwardOp, ForwardOp>
{ using type = State; };



}
}
}

#endif
