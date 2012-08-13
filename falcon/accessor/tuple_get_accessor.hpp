#ifndef _FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP
#define _FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP

#include <tuple>

namespace falcon {

template <typename _Tuple, std::size_t _N>
struct tuple_get_accessor
{
	typedef typename std::tuple_element<_N, _Tuple>::type value_type;
	static constexpr std::size_t position = _N;

	value_type& operator()(_Tuple &t) const
	{
		return std::get<_N>(t);
	}

	constexpr value_type& operator()(const _Tuple &t) const
	{
		return std::get<_N>(t);
	}
};

}

#endif