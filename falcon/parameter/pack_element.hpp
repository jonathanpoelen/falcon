#ifndef FALCON_PARAMETER_PACK_ELEMENT_HPP
#define FALCON_PARAMETER_PACK_ELEMENT_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {

template <typename ResultPack, typename Pack, typename Indexes>
class __pack_element;

template <typename... ResultElements, typename... Elements, std::size_t Index, std::size_t... Indexes>
struct __pack_element<
	parameter_pack<ResultElements...>,
	parameter_pack<Elements...>,
	parameter_index<Index, Indexes...>
>
: __pack_element<
	parameter_pack<
		ResultElements...,
		typename arg_element<Index, Elements...>::type
	>,
	parameter_pack<Elements...>,
	parameter_index<Indexes...>
>
{};

template <typename... ResultElements, typename... Elements>
struct __pack_element<
	parameter_pack<ResultElements...>,
	parameter_pack<Elements...>,
	parameter_index<>
>
{ typedef parameter_pack<ResultElements...> __type; };

template <typename Pack, typename Indexes>
struct pack_element
{
	typedef typename __pack_element<
		parameter_pack<>, Pack, Indexes
	>::__type type;
};

namespace parameter {
  template <typename Pack, typename Indexes>
  using elements = pack_element<Pack, Indexes>;
}

}

#endif
