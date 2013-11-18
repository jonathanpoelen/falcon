#ifndef FALCON_MPL_DETAIL_HAS_KEY_HPP
#define FALCON_MPL_DETAIL_HAS_KEY_HPP

#include <falcon/mpl/key_type.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {
namespace detail {

template<bool, typename Seq, typename Key, typename>
class __has_key;

template<typename Seq, typename Key, typename T, typename... Ts>
struct __has_key<false, Seq, Key, seq<T, Ts...>>
: __has_key<std::is_same<typename key_type<Seq, T>::type, Key>::value, Seq, Key, seq<Ts...>>
{};

template<typename Seq, typename Key, typename... Ts>
struct __has_key<true, Seq, Key, seq<Ts...>>
{ static const bool value = true; };

template<typename Seq, typename Key>
struct __has_key<false, Seq, Key, seq<>>
{ static const bool value = false; };

template<typename Seq, typename Key>
class has_key_impl;

template<template <class...> class Temp, typename Key, typename... Ts>
struct has_key_impl<Temp<Ts...>, Key>
: __has_key<false, Temp<Ts...>, Key, seq<Ts...>>
{};

}
}
}

#endif
