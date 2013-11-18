#ifndef FALCON_MPL_DETAIL_COUNT_HPP
#define FALCON_MPL_DETAIL_COUNT_HPP

#include <falcon/mpl/key_type.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {
namespace detail {

template<std::size_t N, typename Seq, typename Key, typename>
struct __count
{ static const std::size_t value = N; };

template<std::size_t N, typename Seq, typename Key, typename T, typename... Ts>
struct __count<N, Seq, Key, seq<T, Ts...>>
: __count<N+(std::is_same<typename key_type<Seq, T>::type, Key>::value? 1:0)
, Seq, Key, seq<Ts...>>
{};

template<typename Seq, typename Key>
class count_impl;

template<template <class...> class Temp, typename Key, typename... Ts>
struct count_impl<Temp<Ts...>, Key>
: __count<0, Temp<Ts...>, Key, seq<Ts...>>
{};

}
}
}

#endif
