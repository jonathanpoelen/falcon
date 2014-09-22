#ifndef FALCON_UTILITY_INHERITANCE_WITH_INDEX_HPP
#define FALCON_UTILITY_INHERITANCE_WITH_INDEX_HPP

#include <utility>
#include <falcon/arg/arg.hpp>

namespace falcon
{

template<typename Class, std::size_t... ParameterIndexes>
class inheritance_class;

template<typename Inherit, typename... Inherits>
class inheritance_with_index;

template<typename Inherit, std::size_t... Indexes, typename... Inherits>
struct inheritance_with_index<
	inheritance_class<Inherit, Indexes...>,
	Inherits...
>
: Inherit
, inheritance_with_index<Inherits...>
{
	template<typename... _Args>
	inheritance_with_index(_Args&&... args)
	: Inherit(arg<Indexes>(args)...)
	, inheritance_with_index<Inherits...>(std::forward<_Args>(args)...)
	{}
};

template<typename Inherit, std::size_t... Indexes>
struct inheritance_with_index<inheritance_class<Inherit, Indexes...>>
: Inherit
{
	template<typename... _Args>
	inheritance_with_index(_Args&&... args)
	: Inherit(arg<Indexes>(args)...)
	{}
};

}

#endif
