#ifndef FALCON_TUPLE_OPTIMAL_TUPLE_HPP
#define FALCON_TUPLE_OPTIMAL_TUPLE_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/parameter/index_element.hpp>
#include <falcon/parameter/optimal_index_pack.hpp>
#include <falcon/tuple/parameter_pack.hpp>

#include <utility>

namespace falcon {

template<typename _Tuple>
struct optimal_tuple
{
	typedef _Tuple tuple_base;

	typedef typename tuple_to_parameter_pack<_Tuple>::type parameter_pack;

	typedef typename optimal_index_pack<parameter_pack>::type indexes;

	typedef typename parameter_pack_to_tuple<
		typename parameter::pack_element<parameter_pack, indexes>::type
	>::type tuple;
	typedef tuple type;

	template<std::size_t _I>
	struct idx
	{ static const std::size_t value = index_element<_I, indexes>::value; };

	template<std::size_t _I>
	struct tuple_element
	{ typedef typename std::tuple_element<idx<_I>::value, _Tuple>::type type; };

	template<std::size_t _I>
	static typename tuple_element<_I>::type& get(_Tuple& t)
	{ return std::get<idx<_I>::value>(t); }

	template<std::size_t _I>
	static const typename tuple_element<_I>::type& get(const _Tuple& t)
	{ return std::get<idx<_I>::value>(t); }

	template<std::size_t _I>
	static typename tuple_element<_I>::type&& get(_Tuple&& t)
	{ return std::get<idx<_I>::value>(std::forward<_Tuple>(t)); }
};

}

#endif
