#ifndef FALCON_MPL_FOR_EACH_HPP
#define FALCON_MPL_FOR_EACH_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/mpl/detail/seq.hpp>
#include <falcon/mpl/aux_/apply_impl.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/next.hpp>
#include <falcon/mpl/deref.hpp>

namespace falcon {
namespace mpl {

namespace aux {

template<class First, class Last>
struct for_each_iter_impl
{
  template<class F>
  static void exec(F f)
  {
    f(deref_t<First>::value);
    for_each_iter_impl<next_t<First>, Last>::exec(f);
  }
};

template<class Last>
struct for_each_iter_impl<Last, Last>
{
  template<class F>
  static void exec(F)
  {}
};

template<class Seq>
struct for_each_impl
: for_each_iter_impl<begin_t<Seq>, end_t<Seq>>
{};

template<class Tag, class... Ts>
struct for_each_impl<::falcon::mpl::detail::seq<Tag, Ts...>>
{
  template<class F>
  static void exec(F f)
  { FALCON_UNPACK(f(Ts::value)); }
};


template<class First, class Last>
struct for_each_transform_iter_impl
{
  template<class TransformOp, class F>
  static void exec(F f)
  {
    f(aux::apply_impl<TransformOp, deref_t<First>>::type::value);
    for_each_transform_iter_impl<next_t<First>, Last>::template exec<TransformOp>(f);
  }
};

template<class Last>
struct for_each_transform_iter_impl<Last, Last>
{
  template<class TransformOp, class F>
  static void exec(F)
  {}
};

template<class Seq>
struct for_each_transform_impl
: for_each_transform_iter_impl<begin_t<Seq>, end_t<Seq>>
{};

template<class Tag, class... Ts>
struct for_each_transform_impl<::falcon::mpl::detail::seq<Tag, Ts...>>
{
  template<class TransformOp, class F>
  static void exec(F f)
  { FALCON_UNPACK(f(aux::apply_impl<TransformOp, Ts>::type::value)); }
};

}

template<
  class Sequence
, class F
>
void for_each(F f, Sequence * = 0)
{ aux::for_each_impl<Sequence>::exec(f); }

template<
  class Sequence
, class TransformOp
, class F
>
void for_each(F f, Sequence * = 0, TransformOp * = 0)
{ aux::for_each_transform_impl<Sequence>::template exec<TransformOp>(f); }

}
}

#endif
