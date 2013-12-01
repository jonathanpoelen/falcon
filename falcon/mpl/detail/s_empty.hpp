#ifndef FALCON_MPL_DETAIL_S_EMPTY_HPP
#define FALCON_MPL_DETAIL_S_EMPTY_HPP

#include <falcon/arg/arg.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename T>
class s_empty;

template<template <class...> class T, typename... Ts>
struct s_empty<T<Ts...>>
{
  static const bool value = !sizeof...(Ts);
};

}
}
}

#endif
