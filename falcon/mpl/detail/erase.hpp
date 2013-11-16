#ifndef FALCON_MPL_DETAIL_ERASE_HPP
#define FALCON_MPL_DETAIL_ERASE_HPP

#include <falcon/parameter/manip.hpp>
#include <falcon/mpl/detail/insert.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename Seq, std::size_t Pos, std::size_t Last>
class erase_impl;

template<template<class...> class Temp, std::size_t Pos, std::size_t Last, typename... Args>
struct erase_impl<Temp<Args...>, Pos, Last>
{
  using __type = pack_slice<Pos, parameter_pack<Args...>>;
  using type = typename insert_cat_impl<
    Temp
  , typename __type::first_type
  , typename pack_slice<Last-Pos, typename __type::second_type>::second_type
  >::type;
};


}
}
}

#endif
