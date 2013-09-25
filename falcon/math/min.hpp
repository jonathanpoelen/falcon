#ifndef FALCON_MATH_MIN_HPP
#define FALCON_MATH_MIN_HPP

namespace falcon {

template<typename T>
constexpr T min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template<typename T, typename... _Args>
constexpr T min(const T& a, const T& b, const _Args&... args)
{
	return min(a < b ? a : b, args...);
}

}

#endif
