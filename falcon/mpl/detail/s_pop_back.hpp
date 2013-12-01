#ifndef FALCON_MPL_DETAIL_S_POP_BACK_HPP
#define FALCON_MPL_DETAIL_S_POP_BACK_HPP

#include <falcon/mpl/detail/s_erase.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq>
class s_pop_back;

template<template <class...> class Temp, typename... Ts>
struct s_pop_back<Temp<Ts...>>
: s_erase<Temp<Ts...>, sizeof...(Ts)-1>
{};

}
}
}

#endif
