#ifndef _FALCON_TUPLE_TUPLE_PACK_HPP
#define _FALCON_TUPLE_TUPLE_PACK_HPP

#include <falcon/parameter/pack_element.hpp>
#include <falcon/tuple/parameter_pack.hpp>

namespace falcon {

template <typename _Tuple, typename _Indexes>
struct tuple_pack_element;

template <typename... _Elements, std::size_t... _Indexes>
struct tuple_pack_element<std::tuple<_Elements...>, parameter_index<_Indexes...>>
{
	typedef typename parameter_pack_to_tuple<
		typename parameter::pack_element<
			parameter_pack<_Elements...>,
			parameter_index<_Indexes...>
		>::type
	>::type type;
};

}

#endif