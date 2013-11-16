#ifndef FALCON_MPL_APPLY_HPP
#define FALCON_MPL_APPLY_HPP

#include <falcon/sfinae/has_type.hpp>
#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/detail/at.hpp>
#include <falcon/mpl/placeholders.hpp>

namespace falcon {
namespace mpl {

namespace detail {

FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(has_mpl_apply, apply);

template<typename T, typename SeqArgs, bool has_apply = has_mpl_apply<T>::value>
struct apply_impl
{ using type = T; };

template<typename T, typename... Args>
struct apply_impl<T, seq<Args...>, true>
{ using type = typename T::template apply<Args...>::type; };

template<typename T, typename SeqArgs>
struct apply_impl<protect<T>, SeqArgs, false>
{ using type = T; };

template<std::size_t N, typename... Args>
struct apply_impl<placeholders::placeholder<N>, seq<Args...>, true>
{ using type = typename at_impl<seq<Args...>, N-1>::type; };

template <typename T, bool = has_mpl_type_impl<T>(1)>
struct mpl_type_or_type_impl
{ using type = T; };

template <typename T>
struct mpl_type_or_type_impl<T, true>
{ using type = typename T::type; };

template<template<class...> class T, typename... Args, typename SeqArgs>
struct apply_impl<T<Args...>, SeqArgs, false>
{
  using type = typename mpl_type_or_type_impl<
    T<typename apply_impl<Args, SeqArgs>::type...>
  >::type;
};

}

template<typename F, typename... Args>
struct apply
{
  using type = typename detail::apply_impl<F, detail::seq<Args...>>::type;
};

}
}

#endif
