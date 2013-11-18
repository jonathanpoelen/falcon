#ifndef FALCON_MPL_DETAIL_AT_HPP
#define FALCON_MPL_DETAIL_AT_HPP

#include <falcon/arg/arg.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename T, std::size_t N>
class at_impl;

template<template <class...> class T, typename... Args, std::size_t N>
struct at_impl<T<Args...>, N>
{
  static_assert(N < sizeof...(Args), "sequence is too small");
  using type = typename arg_element<N, Args...>::type;
};

}
}
}

#endif
