#ifndef FALCON_MPL_DETAIL_S_POP_FRONT_HPP
#define FALCON_MPL_DETAIL_S_POP_FRONT_HPP

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq>
class s_pop_front;

template<template <class...> class Temp, typename... Ts, typename T>
struct s_pop_front<Temp<T, Ts...>>
{ using type = Temp<Ts...>; };

}
}
}

#endif
