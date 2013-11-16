#ifndef FALCON_MPL_DETAIL_INSERT_HPP
#define FALCON_MPL_DETAIL_INSERT_HPP

#include <falcon/parameter/manip.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<template<class...> class Temp, typename Pack1, typename Pack2, typename...>
class insert_cat_impl;

template<
  template<class...> class Temp
, typename... Es
, typename... Es2
, typename... Ts
>
struct insert_cat_impl<Temp, parameter_pack<Es...>, parameter_pack<Es2...>, Ts...>
{
  using type = Temp<Es..., Ts..., Es2...>;
};

template<typename Seq, std::size_t Pos, typename T>
class insert_impl;

template<template<class...> class Temp, std::size_t Pos, typename T, typename... Args>
struct insert_impl<Temp<Args...>, Pos, T>
{
  using __type = pack_slice<Pos, parameter_pack<Args...>>;
  using type = typename insert_cat_impl<
    Temp
  , typename __type::first_type
  , typename __type::second_type
  , T
  >::type;
};

template<typename Seq, std::size_t Pos, typename Range>
class insert_range_impl;

template<
  template<class...> class Temp, std::size_t Pos
, template<class...> class Temp2, typename... Args, typename... Args2>
struct insert_range_impl<Temp<Args...>, Pos, Temp2<Args2...>>
{
  using __type = pack_slice<Pos, parameter_pack<Args...>>;
  using type = typename insert_cat_impl<
    Temp
  , typename __type::first_type
  , typename __type::second_type
  , Args2...
  >::type;
};

}
}
}

#endif
