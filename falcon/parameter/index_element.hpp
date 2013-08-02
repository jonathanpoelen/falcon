#ifndef FALCON_PARAMETER_INDEX_PARAMETER_HPP
#define FALCON_PARAMETER_INDEX_PARAMETER_HPP

#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <std::size_t __i, typename Pack>
class __index_element;

template <std::size_t _I, std::size_t... Indexes>
struct __index_element<0, parameter_index<_I, Indexes...>>
{ static const std::size_t value = _I; };

template <std::size_t __i, std::size_t _I, std::size_t... Indexes>
struct __index_element<__i, parameter_index<_I, Indexes...>>
: __index_element<
	__i-1,
	parameter_index<Indexes...>
>
{};

template <std::size_t __i, typename Pack>
struct index_element
{ static const std::size_t value = __index_element<__i, Pack>::value; };

namespace parameter {
  template <std::size_t __i, typename Pack>
  using index_at = index_element<__i, Pack>;
}

}

#endif
