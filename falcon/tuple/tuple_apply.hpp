#ifndef _FALCON_TUPLE_TUPLE_APPLY_HPP
#define _FALCON_TUPLE_TUPLE_APPLY_HPP

#include <falcon/tuple/parameter_index.hpp>

namespace falcon {

template <typename _Function, typename _T, std::size_t... _Indexes>
constexpr auto tuple_apply(const parameter_index<_Indexes...>&,
						   const _T& __t, _Function __func)
-> decltype(__func(std::get<_Indexes>(__t)...))
{ return __func(std::get<_Indexes>(__t)...); }

template <typename _Function, typename _T, std::size_t... _Indexes>
constexpr auto tuple_apply(const parameter_index<_Indexes...>&,
						   _T& __t, _Function __func)
-> decltype(__func(std::get<_Indexes>(__t)...))
{ return __func(std::get<_Indexes>(__t)...); }

template <typename _Function, typename _T,
	typename _Indexes = typename build_tuple_index<_T>::type
>
constexpr auto tuple_apply(const _T& __t, _Function __func)
-> decltype(tuple_apply<_Function&>(_Indexes(), __t, __func))
{ return tuple_apply<_Function&>(_Indexes(), __t, __func); }

template <typename _Function, typename _T,
	typename _Indexes = typename build_tuple_index<_T>::type
>
constexpr auto tuple_apply(_T& __t, _Function __func)
-> decltype(tuple_apply<_Function&>(_Indexes(), __t, __func))
{ return tuple_apply<_Function&>(_Indexes(), __t, __func); }

}

#endif