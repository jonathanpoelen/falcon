#ifndef _FALCON_PARAMETER_PACK_ELEMENT_HPP
#define _FALCON_PARAMETER_PACK_ELEMENT_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {
namespace parameter {

template <typename _ResultPack, typename _Pack, typename _Indexes>
class __pack_element;

template <typename... _ResultElements, typename... _Elements, std::size_t _Index, std::size_t... _Indexes>
struct __pack_element<
	parameter_pack<_ResultElements...>,
	parameter_pack<_Elements...>,
	parameter_index<_Index, _Indexes...>
>
: __pack_element<
	parameter_pack<
		_ResultElements...,
		typename arg_element<_Index, _Elements...>::type
	>,
	parameter_pack<_Elements...>,
	parameter_index<_Indexes...>
>
{};

template <typename... _ResultElements, typename... _Elements>
struct __pack_element<
	parameter_pack<_ResultElements...>,
	parameter_pack<_Elements...>,
	parameter_index<>
>
{ typedef parameter_pack<_ResultElements...> __type; };

template <typename _Pack, typename _Indexes>
struct pack_element
{
	typedef typename __pack_element<
		parameter_pack<>, _Pack, _Indexes
	>::__type type;
};

}
}

#endif