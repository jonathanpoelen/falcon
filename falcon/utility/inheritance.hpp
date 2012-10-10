#ifndef FALCON_UTILITY_INHERITANCE_HPP
#define FALCON_UTILITY_INHERITANCE_HPP

#include <utility>

namespace falcon
{

template<typename _Inherit, typename... _Inherits>
struct inheritance
: _Inherit
, inheritance<_Inherits...>
{
	template<typename _T, typename... _Args>
	inheritance(_T&& v, _Args&&... args)
	: _Inherit(std::forward<_T>(v))
	, inheritance<_Inherits...>(std::forward<_Args>(args)...)
	{}
};

template<typename _Inherit>
struct inheritance<_Inherit>
: _Inherit
{
	template<typename... _Args>
	inheritance(_Args&&... args)
	: _Inherit(std::forward<_Args>(args)...)
	{}
};

}

#endif