#ifndef FALCON_UTILITY_INHERITANCE_HPP
#define FALCON_UTILITY_INHERITANCE_HPP

#include <utility>

namespace falcon
{

template<typename Inherit, typename... Inherits>
struct inheritance
: Inherit
, inheritance<Inherits...>
{
	template<typename _T, typename... Args>
	inheritance(_T&& v, Args&&... args)
	: Inherit(std::forward<_T>(v))
	, inheritance<Inherits...>(std::forward<Args>(args)...)
	{}
};

template<typename Inherit>
struct inheritance<Inherit>
: Inherit
{
	template<typename... Args>
	inheritance(Args&&... args)
	: Inherit(std::forward<Args>(args)...)
	{}
};

}

#endif
