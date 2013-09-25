#ifndef FALCON_LOGICAL_VALUE_CONDITION_HPP
#define FALCON_LOGICAL_VALUE_CONDITION_HPP

namespace falcon {

#if __cplusplus >= 201103L
template<typename T>
inline constexpr T& first_true(T& a)
{
	return a;
}

template<typename T, typename... Args>
inline constexpr T& first_true(T& a, Args&... args)
{
	return a ? a : first_true<T>(args...);
}

#else
template<typename T>
inline T& first_true(T& a, T& b)
{
	return a ? a : b;
}
#endif

#if __cplusplus >= 201103L
template<typename T>
inline constexpr T& first_false(T& a)
{
	return a;
}

template<typename T, typename... Args>
inline constexpr T& first_false(T& a, Args&... args)
{
	return a ? first_false<T>(args...) : a;
}

#else
template<typename T>
inline T& first_false(T& a, T& b)
{
	return a ? b : a;
}
#endif

}

#endif
