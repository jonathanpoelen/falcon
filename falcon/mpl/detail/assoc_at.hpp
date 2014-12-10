#ifndef FALCON_MPL_DETAIL_ASSOC_AT_HPP
#define FALCON_MPL_DETAIL_ASSOC_AT_HPP

#include <falcon/functional/arg.hpp>
#include <falcon/mpl/key_type.hpp>
#include <falcon/mpl/value_type.hpp>

#include <type_traits>

namespace falcon {
namespace mpl {
namespace detail {

template<bool, typename Seq, typename Key, typename, typename Default, typename=void>
struct __assoc_at_impl
{ using type = Default; };

template<typename Seq, typename Key, typename T, typename... Ts, typename Default, typename X>
struct __assoc_at_impl<false, Seq, Key, seq<T, Ts...>, Default, X>
: __assoc_at_impl<std::is_same</*typename key_type<Seq, T>::type*/T, Key>::value
, Seq, Key, seq<Ts...>, Default, typename value_type<Seq, T>::type>
{};

template<typename Seq, typename Key, typename... Ts, typename Default, typename X>
struct __assoc_at_impl<true, Seq, Key, seq<Ts...>, Default, X>
{ using type = X; };

template<typename Seq, typename Key, typename Default>
class assoc_at_impl;

template<template <class...> class Temp, typename Key, typename Default, typename... Ts>
struct assoc_at_impl<Temp<Ts...>, Key, Default>
: __assoc_at_impl<false, Temp<Ts...>, Key, seq<Ts...>, Default>
{};

}
}
}

#endif
