#ifndef FALCON_MATH_MAX_HPP
#define FALCON_MATH_MAX_HPP

namespace falcon {

template<typename T>
constexpr T max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template<typename T, typename... _Args>
constexpr T max(const T& a, const T& b, const _Args&... args)
{
	return max<T>(a > b ? a : b, args...);
}

}

#endif
