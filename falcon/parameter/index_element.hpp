#ifndef _FALCON_PARAMETER_INDEX_PARAMETER_HPP
#define _FALCON_PARAMETER_INDEX_PARAMETER_HPP

#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <std::size_t __i, typename _Pack>
class __index_element;

template <std::size_t _I, std::size_t... _Indexes>
struct __index_element<0, parameter_index<_I, _Indexes...>>
{ static const std::size_t value = _I; };

template <std::size_t __i, std::size_t _I, std::size_t... _Indexes>
struct __index_element<__i, parameter_index<_I, _Indexes...>>
: __index_element<
	__i-1,
	parameter_index<_Indexes...>
>
{};

template <std::size_t __i, typename _Pack>
struct index_element
{ static const std::size_t value = __index_element<__i, _Pack>::value; };

}

#endif