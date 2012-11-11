#ifndef _FALCON_TUPLE_PARAMETER_PACK_HPP
#define _FALCON_TUPLE_PARAMETER_PACK_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/parameter/pack_element.hpp>
#include <falcon/type_traits/build_class.hpp>

namespace falcon {

template<typename _T, typename _Indexes>
class tuple_to_parameter_pack_with_parameter_index;

template<typename _Pack, typename _T, std::size_t... _Indexes>
struct __tuple_to_parameter_pack_with_parameter_index
{ typedef _Pack type; };

template<typename _T, typename... _Elements, std::size_t _Index, std::size_t... _Indexes>
struct __tuple_to_parameter_pack_with_parameter_index<parameter_pack<_Elements...>, _T, _Index, _Indexes...>
: __tuple_to_parameter_pack_with_parameter_index<
	parameter_pack<
		_Elements...,
		typename std::tuple_element<_Index, _T>::type
	>, _T, _Indexes...
>{};

template<typename _T, std::size_t... _Indexes>
struct tuple_to_parameter_pack_with_parameter_index<_T, parameter_index<_Indexes...>>
: __tuple_to_parameter_pack_with_parameter_index<parameter_pack<>, _T, _Indexes...>
{};


template<std::size_t _Start, std::size_t _Stop, typename _T, std::size_t _Step = 1>
class build_range_tuple_to_parameter_pack
{
	static const std::size_t __size = std::tuple_size<_T>::value;
	static const std::size_t __stop = (_Stop > __size ? __size : _Stop);
	static const std::size_t __start = (_Start < __stop ? _Start : __stop);
	typedef typename build_range_parameter_index<__start, __stop, _Step>::type __indexes;
public:
	typedef typename tuple_to_parameter_pack_with_parameter_index<_T, __indexes>::type type;
};

template<typename _T>
struct tuple_to_parameter_pack
: tuple_to_parameter_pack_with_parameter_index<
	_T,
	typename build_parameter_index<std::tuple_size<_T>::value>::type
>{};

template<typename _Pack>
struct parameter_pack_to_tuple
: build_class<std::tuple, _Pack>
{};

}

#endif