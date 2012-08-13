#ifndef _FALCON_TUPLE_TO_TUPLE_REFERENCE_HPP
#define _FALCON_TUPLE_TO_TUPLE_REFERENCE_HPP

#include <falcon/parameter/pack_element.hpp>
#include <falcon/tuple/parameter_pack.hpp>

namespace falcon {

///Reference tuple element
template <typename... _Elements, std::size_t... _Indexes>
constexpr typename parameter_pack_to_tuple<
	typename parameter::pack_element<
		parameter_pack<const _Elements&...>,
		parameter_index<_Indexes...>
	>::type
>::type
to_tuple_reference(const std::tuple<_Elements...>& t,
				   const parameter_index<_Indexes...>&)
{ return std::tuple<const _Elements&...>(std::get<_Indexes>(t)...); }

template <typename... _Elements, std::size_t... _Indexes>
constexpr typename parameter_pack_to_tuple<
	typename parameter::pack_element<
		parameter_pack<_Elements&...>,
		parameter_index<_Indexes...>
	>::type
>::type
to_tuple_reference(std::tuple<_Elements...>& t,
				   const parameter_index<_Indexes...>&)
{ return std::tuple<_Elements&...>(std::get<_Indexes>(t)...); }

template <typename... _Elements>
constexpr std::tuple<const _Elements&...>
to_tuple_reference(const std::tuple<_Elements...>& t)
{
	typedef typename build_parameter_index<sizeof...(_Elements)>::type _BuildIndexes;
	return to_tuple_reference(t, _BuildIndexes());
}

template <typename... _Elements>
constexpr std::tuple<_Elements&...>
to_tuple_reference(std::tuple<_Elements...>& t)
{
	typedef typename build_parameter_index<sizeof...(_Elements)>::type _BuildIndexes;
	return to_tuple_reference(t, _BuildIndexes());
}

}

#endif