#ifndef FALCON_MPL_DETAIL_S_ERASE_HPP
#define FALCON_MPL_DETAIL_S_ERASE_HPP

#include <falcon/parameter/manip.hpp>
#include <falcon/mpl/detail/s_insert.hpp>
#include <falcon/mpl/detail/na.hpp>
#include <falcon/mpl/integral_c.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq, std::size_t Pos, typename Last = na>
class s_erase;

template<template<class...> class Temp, std::size_t Pos, typename Last, typename... Ts>
struct s_erase<Temp<Ts...>, Pos, Last>
{
  using __type = pack_slice<Pos, parameter_pack<Ts...>>;
  using type = typename insert_cat_impl<
    Temp
  , typename __type::first_type
  , typename pack_slice<Last::value-Pos, typename __type::second_type>::second_type
  >::type;
};

template<template<class...> class Temp, std::size_t Pos, typename... Ts>
struct s_erase<Temp<Ts...>, Pos, na>
{
  using __type = pack_slice<Pos, parameter_pack<Ts...>>;
  using type = typename insert_cat_impl<
    Temp
  , typename __type::first_type
  , typename __type::second_type
  >::type;
};


}
}
}

#endif
