#ifndef FALCON_UTILITY_INHERITANCE_WITH_INDEX_HPP
#define FALCON_UTILITY_INHERITANCE_WITH_INDEX_HPP

#include <utility>
#include <falcon/arg/arg.hpp>

namespace falcon
{

template<typename _Class, std::size_t... _ParameterIndexes>
class inheritance_class;

template<typename _Inherit, typename... _Inherits>
class inheritance_with_index;

template<typename _Inherit, std::size_t... _Indexes, typename... _Inherits>
struct inheritance_with_index<
	inheritance_class<_Inherit, _Indexes...>,
	_Inherits...
>
: _Inherit
, inheritance_with_index<_Inherits...>
{
	template<typename... _Args>
	inheritance_with_index(_Args&&... args)
	: _Inherit(arg<_Indexes>(args)...)
	, inheritance_with_index<_Inherits...>(std::forward<_Args>(args)...)
	{}
};

template<typename _Inherit, std::size_t... _Indexes>
struct inheritance_with_index<inheritance_class<_Inherit, _Indexes...>>
: _Inherit
{
	template<typename... _Args>
	inheritance_with_index(_Args&&... args)
	: _Inherit(arg<_Indexes>(args)...)
	{}
};

}

#endif