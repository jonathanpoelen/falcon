#ifndef FALCON_MATH_ABS_DIFF_HPP
#define FALCON_MATH_ABS_DIFF_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
///Return @p b - @p a if @p a is less @p b, otherwise return @p a - @p b
template <typename T>
inline CPP_CONSTEXPR T abs_diff(const T& a, const T& b)
{
	return a < b ? b - a : a - b;
}
}

#endif
