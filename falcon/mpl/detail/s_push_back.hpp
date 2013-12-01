#ifndef FALCON_MPL_DETAIL_S_PUSH_BACK_HPP
#define FALCON_MPL_DETAIL_S_PUSH_BACK_HPP

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq, typename T>
class s_push_back;

template<template <class...> class Temp, typename... Ts, typename T>
struct s_push_back<Temp<Ts...>, T>
{ using type = Temp<Ts..., T>; };

}
}
}

#endif
