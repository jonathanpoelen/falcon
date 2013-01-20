#ifndef TUPLE_DETAIL_TUPLEFWD_HPP
#define TUPLE_DETAIL_TUPLEFWD_HPP

#include <cstddef>

namespace falcon
{
	template<typename>
	class __surrogate_std_tuple;
}

namespace std
{
	template<typename...>
	class tuple;

	template<std::size_t __i, typename _Tp>
	class tuple_element;

	template<typename _Tp>
	class tuple_size;

	template<std::size_t _Int, typename _Tp>
	int get(::falcon::__surrogate_std_tuple<_Tp>);
}

#endif