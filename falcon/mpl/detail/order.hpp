#ifndef FALCON_MPL_DETAIL_ORDER_HPP
#define FALCON_MPL_DETAIL_ORDER_HPP

#include <falcon/mpl/key_type.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {
namespace detail {

template<bool, typename Seq, typename Key, typename>
struct __order
{ static const std::size_t value = -1u; };

template<typename Seq, typename Key, typename T, typename... Ts>
struct __order<false, Seq, Key, seq<T, Ts...>>
: __order<std::is_same<typename key_type<Seq, T>::type, Key>::value, Seq, Key, seq<Ts...>>
{};

template<typename Seq, typename Key, typename... Ts>
struct __order<true, Seq, Key, seq<Ts...>>
{ static const std::size_t value = sizeof...(Ts)+1; };

template<typename Seq, typename Key>
class order_impl;

template<template <class...> class Temp, typename Key, typename... Ts>
struct order_impl<Temp<Ts...>, Key>
: __order<false, Temp<Ts...>, Key, seq<Ts...>>
{};

}
}
}

#endif
