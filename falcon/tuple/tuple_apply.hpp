#ifndef _FALCON_TUPLE_TUPLE_APPLY_HPP
#define _FALCON_TUPLE_TUPLE_APPLY_HPP

#include <tuple>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <typename _Function, typename... _Elements, std::size_t... _Indexes>
constexpr auto tuple_apply(const parameter_index<_Indexes...>&,
						   _Function __func,
						   const std::tuple<_Elements...>& __t)
-> decltype(__func(std::get<_Indexes>(__t)...))
{ return __func(std::get<_Indexes>(__t)...); }

template <typename _Function, typename... _Elements, std::size_t... _Indexes>
constexpr auto tuple_apply(const parameter_index<_Indexes...>&,
						   _Function __func,
						   std::tuple<_Elements...>& __t)
-> decltype(__func(std::get<_Indexes>(__t)...))
{ return __func(std::get<_Indexes>(__t)...); }

template <typename _Function, typename... _Elements,
	typename _Indexes = typename build_parameter_index<
		sizeof...(_Elements)
	>::type
>
constexpr auto tuple_apply(_Function __func,
						   const std::tuple<_Elements...>& __t)
-> decltype(tuple_apply<_Function&>(_Indexes(), __func, __t))
{ return tuple_apply<_Function&>(_Indexes(), __func, __t); }

template <typename _Function, typename... _Elements,
	typename _Indexes = typename build_parameter_index<
		sizeof...(_Elements)
	>::type
>
constexpr auto tuple_apply(_Function __func,
						   std::tuple<_Elements...>& __t)
-> decltype(tuple_apply<_Function&>(_Indexes(), __func, __t))
{ return tuple_apply<_Function&>(_Indexes(), __func, __t); }

}

#endif