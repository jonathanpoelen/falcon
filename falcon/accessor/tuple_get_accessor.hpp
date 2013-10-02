#ifndef FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP
#define FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>

namespace falcon {

template <typename Tuple, std::size_t N>
struct tuple_get_accessor
{
	typedef typename std::tuple_element<N, Tuple>::type result_type;
	typedef Tuple argument_type;

	static constexpr std::size_t index = N;

	result_type& operator()(Tuple &t) const
	{
		return get<N>(t);
	}

	constexpr const result_type& operator()(const Tuple &t) const
	{
		return get<N>(t);
	}
};

}

#endif
