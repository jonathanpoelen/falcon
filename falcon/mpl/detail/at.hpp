#ifndef FALCON_MPL_DETAIL_AT_HPP
#define FALCON_MPL_DETAIL_AT_HPP

#include <falcon/arg/arg.hpp>

namespace falcon {
namespace mpl {

class na;

namespace detail {
template<typename T, std::size_t N>
struct at_impl
{ using type = na; };

template<bool, std::size_t N, typename... Args>
struct at_impl2
{ using type = na; };

template<std::size_t N, typename... Args>
struct at_impl2<true, N, Args...>
{ using type = typename arg_element<N, Args...>::type; };

template<template <class...> class T, typename... Args, std::size_t N>
struct at_impl<T<Args...>, N>
{ using type = typename at_impl2<(N < sizeof...(Args)), N, Args...>::type; };
}

}
}

#endif
