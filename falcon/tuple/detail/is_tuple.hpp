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
struct __is_tuple
: std::false_type
{};

template<typename... _Elements>
struct __is_tuple<std::tuple<_Elements...>>
: std::true_type
{};


namespace detail {

template<typename _T>
struct has_tuple_impl
: __is_tuple<_T>
{};

template<typename _T, std::size_t _N>
struct has_tuple_impl<std::array<_T, _N>>
: std::true_type
{};

}

}

#endif