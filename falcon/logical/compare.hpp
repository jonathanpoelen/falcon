#ifndef FALCON_LOGICAL_COMPARE_HPP
#define FALCON_LOGICAL_COMPARE_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
template<typename _T, typename _U = _T,
		int _Lesser = -1,
		int _Greater = -_Lesser,
		int _Equaler = 0
		>
CPP_CONSTEXPR int compare(const _T& a, const _U& b)
{
	return a == b ? _Equaler : a < b ? _Lesser : _Greater;
}

template<int _Lesser, int _Greater, int _Equaler,
		typename _T,
		typename _U = _T
		>
inline CPP_CONSTEXPR int compare(const _T& a, const _U& b)
{
	return compare<_T, _U, _Lesser, _Greater, _Equaler>(a, b);
}

#if __cplusplus >= 201103L
template<typename _T, typename _U = _T, typename _Result>
constexpr _Result compare(const _T& a, const _U& b, _Result&& is_equal, _Result&& is_less, _Result&& is_greater)
{
	return a == b ? is_equal : a < b ? is_less : is_greater;
}
#endif

#if __cplusplus >= 201103L
template<
int _Lesser, int _Greater, int _Equaler,
	typename _T, typename _U
	>
constexpr int mcompare(const _T& a, const _U& b)
{
	return compare<_T,_U, _Lesser, _Greater, _Equaler>(a,b);
}

template<
int _Lesser, int _Greater, int _Equaler,
	typename _T, typename _U, typename... _Others
	>
constexpr int mcompare(const _T& a, const _U& b, const _Others&... other)
{
	return compare<_T,_U, _Lesser, _Greater, _Equaler>(a,b)
		+ mcompare<_Lesser, _Greater, _Equaler>(a, other...);
}

template<typename _T, typename... _Others>
inline constexpr int mcompare(const _T& a, const _Others&... other)
{
	return mcompare<-1, 1, 0>(a, other...);
}
#else
template<int _Lesser, int _Greater, int _Equaler, typename _T>
inline int mcompare(...);
#endif

}

#endif
