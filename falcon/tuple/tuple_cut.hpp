#ifndef _FALCON_TUPLE_TUPLE_CUT_HPP
#define _FALCON_TUPLE_TUPLE_CUT_HPP

#include <falcon/parameter/pack_element.hpp>
#include <falcon/tuple/parameter_pack.hpp>

namespace falcon {

template <typename... _Elements, std::size_t... _Indexes,
typename _Tuple = typename parameter_pack_to_tuple<
	typename parameter::pack_element<
		parameter_pack<_Elements...>,
		parameter_index<_Indexes...>
	>::type
>::type>
_Tuple tuple_cut(std::tuple<_Elements...>& t, const parameter_index<_Indexes...>&)
{
	return _Tuple(std::get<_Indexes>(t)...);
}

}

#endif