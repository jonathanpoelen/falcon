#ifndef _FALCON_MATH_ABS_DIFF_HPP
#define _FALCON_MATH_ABS_DIFF_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
///Return @p b - @p a if @p a is less @p b, otherwise return @p a - @p b
template <typename _T>
inline CPP_CONSTEXPR _T abs_diff(const _T& a, const _T& b)
{
	return a < b ? b - a : a - b;
}
}

#endif
