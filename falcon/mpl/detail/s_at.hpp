#ifndef FALCON_MPL_DETAIL_S_AT_HPP
#define FALCON_MPL_DETAIL_S_AT_HPP

#include <falcon/functional/arg.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename T, std::size_t N>
class s_at;

template<template <class...> class T, typename... Ts, std::size_t N>
struct s_at<T<Ts...>, N>
{
  static_assert(N < sizeof...(Ts), "sequence is too small");
  using type = typename arg_element<N, Ts...>::type;
};

}
}
}

#endif
