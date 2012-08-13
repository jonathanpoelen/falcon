#ifndef _FALCON_MATH_MIN_HPP
#define _FALCON_MATH_MIN_HPP

namespace falcon {

template<typename _T>
constexpr _T min(const _T& a, const _T& b)
{
	return a < b ? a : b;
}

template<typename _T, typename... _Args>
constexpr _T min(const _T& a, const _T& b, const _Args&... args)
{
	return min(a < b ? a : b, args...);
}

}

#endif
