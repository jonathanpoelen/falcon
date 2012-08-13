#ifndef _FALCON_TUPLE_TO_TUPLE_POINTER_HPP
#define _FALCON_TUPLE_TO_TUPLE_POINTER_HPP

#include <falcon/parameter/pack_element.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/tuple/tuple_transform.hpp>
#include <falcon/functional/operators.hpp>

namespace falcon {

/// Pointer tuple element
template <typename... _Elements, std::size_t... _Indexes>
constexpr typename parameter_pack_to_tuple<
	typename parameter::pack_element<
		parameter_pack<const _Elements*...>,
		parameter_index<_Indexes...>
	>::type
>::type
to_tuple_pointer(const std::tuple<_Elements...>& t,
				 const parameter_index<_Indexes...>& indexes)
{ return tuple_transform<>(indexes, t, late_address()); }

template <typename... _Elements, std::size_t... _Indexes>
constexpr typename parameter_pack_to_tuple<
	typename parameter::pack_element<
		parameter_pack<_Elements*...>,
		parameter_index<_Indexes...>
	>::type
>::type
to_tuple_pointer(std::tuple<_Elements...>& t,
				 const parameter_index<_Indexes...>& indexes)
{ return tuple_transform<>(indexes, t, late_address()); }

template <typename... _Elements>
constexpr std::tuple<const _Elements*...>
to_tuple_pointer(const std::tuple<_Elements...>& t)
{
	typedef typename build_parameter_index<sizeof...(_Elements)>::type _BuildIndexes;
	return tuple_transform<>(t, late_address(), _BuildIndexes());
}

template <typename... _Elements>
constexpr std::tuple<_Elements*...>
to_tuple_pointer(std::tuple<_Elements...>& t)
{
	typedef typename build_parameter_index<sizeof...(_Elements)>::type _BuildIndexes;
	return tuple_transform<>(t, late_address(), _BuildIndexes());
}

}

#endif