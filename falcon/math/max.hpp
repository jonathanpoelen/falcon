#ifndef _FALCON_MATH_MAX_HPP
#define _FALCON_MATH_MAX_HPP

namespace falcon {

template<typename _T>
constexpr _T max(const _T& a, const _T& b)
{
	return a > b ? a : b;
}

template<typename _T, typename... _Args>
constexpr _T max(const _T& a, const _T& b, const _Args&... args)
{
	return max<_T>(a > b ? a : b, args...);
}

}

#endif
