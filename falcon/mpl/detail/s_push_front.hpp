#ifndef FALCON_MPL_DETAIL_S_PUSH_FRONT_HPP
#define FALCON_MPL_DETAIL_S_PUSH_FRONT_HPP

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq, typename T>
class s_push_front;

template<template <class...> class Temp, typename... Ts, typename T>
struct s_push_front<Temp<Ts...>, T>
{ using type = Temp<T, Ts...>; };

}
}
}

#endif
