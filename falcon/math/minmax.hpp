#ifndef _FALCON_MATH_MINMAX_HPP
#define _FALCON_MATH_MINMAX_HPP

#include <falcon/math/min.hpp>
#include <falcon/math/max.hpp>
#include <utility>

namespace falcon {

template<typename _T, typename... _Args>
std::pair<const _T&, const _T&> minmax(const _T& a, const _Args&... args)
{
	return std::pair<const _T&, const _T&>(min(a, args...), max(a, args...));
}

}

#endif
