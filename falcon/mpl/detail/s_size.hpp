#ifndef FALCON_MPL_DETAIL_S_SIZE_HPP
#define FALCON_MPL_DETAIL_S_SIZE_HPP

#include <falcon/functional/arg.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename T>
class s_size;

template<template <class...> class T, typename... Ts>
struct s_size<T<Ts...>>
{
  static const std::size_t value = sizeof...(Ts);
};

}
}
}

#endif
