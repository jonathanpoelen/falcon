#ifndef _TUPLE_DETAIL_IS_TUPLE_HPP
#define _TUPLE_DETAIL_IS_TUPLE_HPP

#include <type_traits>
#include <falcon/tuple/detail/tuplefwd.hpp>

namespace std
{
  template<typename, std::size_t>
  class array;
}

namespace falcon {

template<typename>
struct is_tuple
: std::false_type
{};

template<typename... _Elements>
struct is_tuple<std::tuple<_Elements...>>
: std::true_type
{};

template<typename _T>
struct is_tuple_impl
: std::false_type
{};

template<typename... _Elements>
struct is_tuple_impl<std::tuple<_Elements...>>
: std::true_type
{};

template<typename _T, std::size_t _N>
struct is_tuple_impl<std::array<_T, _N>>
: std::true_type
{};

}

#endif
