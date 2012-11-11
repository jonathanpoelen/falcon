#ifndef _FALCON_TUPLE_TO_TUPLE_POINTER_HPP
#define _FALCON_TUPLE_TO_TUPLE_POINTER_HPP

#include <tuple>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/build_tuple_pointer.hpp>
#include <falcon/tuple/tuple_transform.hpp>
#include <falcon/functional/operators.hpp>

namespace falcon {

/// Pointer tuple element
template <typename _T, std::size_t... _Indexes>
constexpr typename build_tuple_const_pointer<_T, parameter_index<_Indexes...>>::type
to_tuple_pointer(const _T& t, const parameter_index<_Indexes...>& indexes)
{ return tuple_transform<>(indexes, t, late_address()); }

template <typename _T, std::size_t... _Indexes>
constexpr typename build_tuple_pointer<_T, parameter_index<_Indexes...>>::type
to_tuple_pointer(_T& t, const parameter_index<_Indexes...>& indexes)
{ return tuple_transform<>(indexes, t, late_address()); }


template <typename _T>
constexpr typename build_tuple_const_pointer<
	_T, typename build_tuple_index<_T>::type
>::type
to_tuple_pointer(const _T& t)
{
	typedef typename build_tuple_index<_T>::type _BuildIndexes;
	return tuple_transform<>(t, late_address(), _BuildIndexes());
}

template <typename _T>
constexpr typename build_tuple_pointer<
	_T, typename build_tuple_index<_T>::type
>::type
to_tuple_pointer(_T& t)
{
	typedef typename build_tuple_index<_T>::type _BuildIndexes;
	return tuple_transform<>(t, late_address(), _BuildIndexes());
}

}

#endif