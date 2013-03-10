#ifndef _FALCON_TUPLE_TO_TUPLE_REFERENCE_HPP
#define _FALCON_TUPLE_TO_TUPLE_REFERENCE_HPP

#include <tuple>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/build_tuple_reference.hpp>

namespace falcon {

///Reference tuple element
template <typename _T, std::size_t... _Indexes>
constexpr typename build_tuple_const_reference<
	_T, parameter_index<_Indexes...>
>::type
to_tuple_reference(const _T& t, const parameter_index<_Indexes...>&)
{
	return typename build_tuple_const_reference<
		_T, parameter_index<_Indexes...>
	>::type(std::get<_Indexes>(t)...);
}

///Reference tuple element
template <typename _T, std::size_t... _Indexes>
constexpr typename build_tuple_reference<
	_T, parameter_index<_Indexes...>
>::type
to_tuple_reference(_T& t, const parameter_index<_Indexes...>&)
{
	return typename build_tuple_reference<
		_T, parameter_index<_Indexes...>
	>::type(std::get<_Indexes>(t)...);
}


///Reference tuple element
template <typename _T>
constexpr typename build_tuple_const_reference<
	_T, typename build_tuple_index<_T>::type
>::type
to_tuple_reference(const _T& t)
{
	typedef typename build_tuple_index<_T>::type _BuildIndexes;
	return to_tuple_reference(t, _BuildIndexes());
}

///Reference tuple element
template <typename _T>
constexpr typename build_tuple_reference<
	_T,
	typename build_tuple_index<_T>::type
>::type
to_tuple_reference(_T& t)
{
	typedef typename build_tuple_index<_T>::type _BuildIndexes;
	return to_tuple_reference(t, _BuildIndexes());
}

}

#endif