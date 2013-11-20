#ifndef FALCON_MPL_DETAIL_ASSOC_INSERT_HPP
#define FALCON_MPL_DETAIL_ASSOC_INSERT_HPP

#include <falcon/arg/arg.hpp>
#include <falcon/mpl/detail/has_key.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq, typename T, bool = has_key_impl<Seq, typename key_type<Seq, T>::type>::value>
struct assoc_insert_impl
{ using type = Seq;};

template<template <class...> class Temp, typename... Ts, typename T>
struct assoc_insert_impl<Temp<Ts...>, T, true>
{ using type = Temp<T, Ts...>;};

}
}
}

#endif
