#ifndef FALCON_MPL_AUX__APPLY_HPP
#define FALCON_MPL_AUX__APPLY_HPP

#include <falcon/mpl/protect.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/detail/s_front.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<typename F, typename...>
class apply_impl;

template<typename F, typename Seq>
struct dispath_apply_impl
{ using type = typename use_if<use_type<F>, use<F>>::type; };

template<typename F, typename T, typename Seq>
struct apply_element
: dispath_apply_impl<T, Seq>
{};

template<typename F, typename T, typename Seq>
struct apply_element<F, protect<T>, Seq>
{ using type = T; };

template<typename F, std::size_t N, typename... Ts>
struct apply_element<F, arg<N>, parameter_pack<Ts...>>
: arg<N>::template apply<Ts...>
{};

template<template<class...> class Tpl, typename... Args, typename Seq>
struct dispath_apply_impl<Tpl<Args...>, Seq>
{ using type = typename Tpl<typename apply_element<Tpl<Args...>, Args, Seq>::type...>::type; };

template<template<class...> class Tpl, typename... Args, typename... Ts>
struct apply_impl<Tpl<Args...>, Ts...>
: dispath_apply_impl<Tpl<Args...>, parameter_pack<Ts...>>
{};

}
}
}

#endif
