#ifndef _FALCON_PARAMETER_PARAMETER_ELEMENT_HPP
#define _FALCON_PARAMETER_PARAMETER_ELEMENT_HPP

#include <cstddef>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {

template <std::size_t __i, typename _Pack>
class __parameter_element;

template <typename _T, typename... _Elements>
struct __parameter_element<0, parameter_pack<_T, _Elements...>>
{
	typedef _T __type;
};

template <typename _T, typename... _Elements>
struct __parameter_element<0, parameter_pack<const _T, _Elements...>>
{
	typedef const _T __type;
};

template <typename _T, typename... _Elements>
struct __parameter_element<0, parameter_pack<volatile _T, _Elements...>>
{
	typedef volatile _T __type;
};

template <typename _T, typename... _Elements>
struct __parameter_element<0, parameter_pack<const volatile _T, _Elements...>>
{
	typedef const volatile _T __type;
};

template <std::size_t __i, typename _T, typename... _Elements>
struct __parameter_element<__i, parameter_pack<_T, _Elements...>>
{
	typedef typename __parameter_element<
		__i-1,
		parameter_pack<_Elements...>
	>::__type __type;
};

template <std::size_t __i, typename _Pack>
struct parameter_element
{ typedef typename __parameter_element<__i, _Pack>::__type type; };

}

#endif