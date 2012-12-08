#ifndef _FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP
#define _FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP

#include <tuple>

namespace falcon {

template <typename _Tuple, std::size_t _N>
struct tuple_get_accessor
{
	typedef typename std::tuple_element<_N, _Tuple>::type& result_type;
	typedef _Tuple argument_type;

	static constexpr std::size_t index = _N;

	result_type operator()(_Tuple &t) const
	{
		return std::get<_N>(t);
	}

	constexpr const result_type operator()(const _Tuple &t) const
	{
		return std::get<_N>(t);
	}
};

}

#endif