#ifndef FALCON_MPL_AUX__APPLY_HPP
#define FALCON_MPL_AUX__APPLY_HPP

#include <falcon/mpl/protect.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/tpl.hpp>
#include <falcon/mpl/detail/s_front.hpp>
#include <falcon/mpl/aux_/is_arg.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/type_traits/or.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<typename F, typename...>
class apply_impl;

template<typename F, typename Seq>
struct dispath_apply_impl
: use_if<use_type<F>, use<F>>
{};

template<typename F, typename T, typename Seq>
class apply_element;

template<typename F, typename T, typename... Ts>
struct apply_element<F, T, parameter_pack<Ts...>>
: apply_impl<T, Ts...>
{};

template<typename F, typename T, typename... Ts>
struct apply_element<F, protect<T>, parameter_pack<Ts...>>
{ using type = T; };

template<typename F, std::size_t N, typename... Ts>
struct apply_element<F, arg<N>, parameter_pack<Ts...>>
: arg<N>::template apply<Ts...>
{};

template<template<class...> class Tpl, typename... Args, typename Seq>
struct dispath_apply_impl<Tpl<Args...>, Seq>
{ using type = typename Tpl<typename apply_element<Tpl<Args...>, Args, Seq>::type...>::type; };

template<typename F, typename... Args>
struct apply_inner_apply
{ using type = typename F::template apply<Args...>::type; };

template<template<class...> class Tpl, typename... Args, typename... Ts>
struct apply_impl<Tpl<Args...>, Ts...>
: ::falcon::if_c_t<
  or_<is_arg<Args>::value...>
, dispath_apply_impl<Tpl<Args...>, parameter_pack<Ts...>>
, apply_inner_apply<Tpl<Args...>, Args...>
>
{};

template<typename F, typename... Args>
struct apply_impl
: apply_inner_apply<F, Args...>
{};

}
}
}

#endif
