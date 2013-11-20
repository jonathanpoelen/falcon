#ifndef FALCON_MPL_DETAIL_ASSOC_ERASE_HPP
#define FALCON_MPL_DETAIL_ASSOC_ERASE_HPP

#include <falcon/mpl/key_type.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq, typename Key, typename, typename>
class __assoc_erase;

template<typename Seq, typename Key, typename Seq1, typename Seq2, typename T
, bool = std::is_same<typename key_type<Seq, T>::type, Key>::value>
class __dispatch_assoc_erase;

template<template <class...> class Temp
, typename Key, typename... Ts, typename... Us, typename T>
struct __dispatch_assoc_erase<Temp<>, Key, seq<T, Ts...>, seq<Us...>, T, true>
{ using type = Temp<Ts..., Us...>; };

template<typename Seq, typename Key, typename... Ts, typename... Us, typename T>
struct __dispatch_assoc_erase<Seq, Key, seq<T, Ts...>, seq<Us...>, T, false>
: __assoc_erase<Seq, Key, seq<T, Ts...>, seq<Us..., T>>
{};

template<typename Seq, typename Key, typename T, typename... Ts, typename... Us>
struct __assoc_erase<Seq, Key, seq<T, Ts...>, seq<Us...>>
: __dispatch_assoc_erase<Seq, Key, seq<Ts...>, seq<Us...>, T>
{};

template<typename Seq, typename Key>
class assoc_erase_impl;

template<template <class...> class Temp, typename Key, typename T, typename... Ts>
struct assoc_erase_impl<Temp<T, Ts...>, Key>
: __assoc_erase<Temp<>, Key, seq<Ts...>, T>
{};

}
}
}

#endif
