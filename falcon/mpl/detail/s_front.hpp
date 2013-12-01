#ifndef FALCON_MPL_DETAIL_S_FRONT_HPP
#define FALCON_MPL_DETAIL_S_FRONT_HPP

namespace falcon {
namespace mpl {
namespace detail {

template<typename T>
class s_front;

template<template <class...> class T, typename U, typename... Ts>
struct s_front<T<U, Ts...>>
{ using type = U; };

}
}
}

#endif
