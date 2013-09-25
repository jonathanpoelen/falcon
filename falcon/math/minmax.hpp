#ifndef FALCON_MATH_MINMAX_HPP
#define FALCON_MATH_MINMAX_HPP

#include <falcon/math/min.hpp>
#include <falcon/math/max.hpp>
#include <utility>

namespace falcon {

template<typename T, typename... _Args>
std::pair<const T&, const T&> minmax(const T& a, const _Args&... args)
{
	return std::pair<const T&, const T&>(min(a, args...), max(a, args...));
}

}

#endif
