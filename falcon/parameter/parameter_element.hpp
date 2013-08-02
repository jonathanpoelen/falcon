#ifndef FALCON_PARAMETER_PARAMETER_ELEMENT_HPP
#define FALCON_PARAMETER_PARAMETER_ELEMENT_HPP

#include <cstddef>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {

template <std::size_t __i, typename Pack>
class __parameter_element;

template <typename T, typename... Elements>
struct __parameter_element<0, parameter_pack<T, Elements...>>
{
	typedef T __type;
};

template <typename T, typename... Elements>
struct __parameter_element<0, parameter_pack<const T, Elements...>>
{
	typedef const T __type;
};

template <typename T, typename... Elements>
struct __parameter_element<0, parameter_pack<volatile T, Elements...>>
{
	typedef volatile T __type;
};

template <typename T, typename... Elements>
struct __parameter_element<0, parameter_pack<const volatile T, Elements...>>
{
	typedef const volatile T __type;
};

template <std::size_t __i, typename T, typename... Elements>
struct __parameter_element<__i, parameter_pack<T, Elements...>>
{
	typedef typename __parameter_element<
		__i-1,
		parameter_pack<Elements...>
	>::__type __type;
};

template <std::size_t __i, typename Pack>
struct parameter_element
{ typedef typename __parameter_element<__i, Pack>::__type type; };


namespace parameter {
  template <std::size_t __i, typename Pack>
  using at = ::falcon::parameter_element<__i, Pack>;
}

}

#endif
