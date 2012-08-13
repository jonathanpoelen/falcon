#ifndef _FALCON_LOGICAL_RANGE_COMPARISONS_HPP
#define _FALCON_LOGICAL_RANGE_COMPARISONS_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template<typename _T>
CPP_CONSTEXPR bool between(const _T& left, const _T& v, const _T& right)
{
	return left < v && v < right;
}

template<typename _T>
CPP_CONSTEXPR bool inner(const _T& left, const _T& v, const _T& right)
{
	return left <= v && v <= right;
}

template<typename _T>
CPP_CONSTEXPR bool outside(const _T& left, const _T& v, const _T& right)
{
	return v < left || right < v;
}

template<typename _T>
CPP_CONSTEXPR bool inner_out(const _T& left, const _T& v, const _T& right)
{
	return v <= left || right <= v;
}


template<typename _T, typename _Functor>
CPP_CONSTEXPR bool between(const _T& left, const _T& v, const  _T& right, _Functor f)
{
	return between<>(f(left), f(v), f(right));
}

template<typename _T, typename _Functor>
CPP_CONSTEXPR bool inner(const _T& left, const _T& v, const  _T& right, _Functor f)
{
	return inner<>(f(left), f(v), f(right));
}

template<typename _T, typename _Functor>
CPP_CONSTEXPR bool outside(const _T& left, const _T& v, const  _T& right, _Functor f)
{
	return outside<>(f(left), f(v), f(right));
}

template<typename _T, typename _Functor>
CPP_CONSTEXPR bool inner_out(const _T& left, const _T& v, const  _T& right, _Functor f)
{
	return inner_out<>(f(left), f(v), f(right));
}
}

#endif
