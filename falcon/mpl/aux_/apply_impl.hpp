#ifndef FALCON_MPL_AUX__APPLY_HPP
#define FALCON_MPL_AUX__APPLY_HPP

#include <falcon/mpl/protect.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/tpl.hpp>
#include <falcon/mpl/detail/s_front.hpp>
#include <falcon/mpl/aux_/is_arg.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/helper/use_type.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use_if.hpp>
#include <falcon/type_traits/or.hpp>

namespace falcon {
namespace mpl {


template<typename F, typename... Args>
class apply;

namespace aux {

template<typename F, typename...>
class apply_impl;

template<typename T, typename Pack>
struct apply_element
{ using type = T; };

template<template<class...> class Tpl, typename... Args, typename Pack>
struct apply_element<Tpl<Args...>, Pack>
{ using type = Tpl<typename apply_element<Args, Pack>::type...>; };

template<typename T, typename Pack>
struct apply_element<protect<T>, Pack>
{ using type = T; };

template<std::size_t N, typename... Ts>
struct apply_element<arg<N>, parameter_pack<Ts...>>
: arg<N>::template apply<Ts...>
{};

template<typename T, typename... Args, typename Pack>
struct apply_element<apply<T, Args...>, Pack>
{ using type = apply<T, typename apply_element<Args, Pack>::type...>; };

template<typename F, typename... Args>
struct apply_inner_apply
{ using type = typename F::template apply<Args...>::type; };

template<template<class...> class Tpl, typename... Args, typename... Ts>
struct apply_impl<Tpl<Args...>, Ts...>
{
  using __elem = Tpl<typename apply_element<Args, parameter_pack<Ts...>>::type...>;
  using type = ::falcon::eval_if_c_t<
    ::falcon::or_c<is_arg<Args>...>
  , use_type<__elem>
  , use_if<
      use_type<__elem>
    , apply_inner_apply<__elem, Args...>
    >
  >;
};

template<typename F, typename... Args>
struct apply_impl
: apply_inner_apply<F, Args...>
{};

}
}
}

#endif
