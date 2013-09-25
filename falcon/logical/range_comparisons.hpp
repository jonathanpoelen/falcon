#ifndef FALCON_LOGICAL_RANGE_COMPARISONS_HPP
#define FALCON_LOGICAL_RANGE_COMPARISONS_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template<typename T>
CPP_CONSTEXPR bool between(const T& left, const T& v, const T& right)
{
	return left < v && v < right;
}

template<typename T>
CPP_CONSTEXPR bool inner(const T& left, const T& v, const T& right)
{
	return left <= v && v <= right;
}

template<typename T>
CPP_CONSTEXPR bool outside(const T& left, const T& v, const T& right)
{
	return v < left || right < v;
}

template<typename T>
CPP_CONSTEXPR bool inner_out(const T& left, const T& v, const T& right)
{
	return v <= left || right <= v;
}


template<typename T, typename Functor>
CPP_CONSTEXPR bool between(const T& left, const T& v, const  T& right, Functor f)
{
	return between(f(left), f(v), f(right));
}

template<typename T, typename Functor>
CPP_CONSTEXPR bool inner(const T& left, const T& v, const  T& right, Functor f)
{
	return inner(f(left), f(v), f(right));
}

template<typename T, typename Functor>
CPP_CONSTEXPR bool outside(const T& left, const T& v, const  T& right, Functor f)
{
	return outside(f(left), f(v), f(right));
}

template<typename T, typename Functor>
CPP_CONSTEXPR bool inner_out(const T& left, const T& v, const  T& right, Functor f)
{
	return inner_out(f(left), f(v), f(right));
}
}

#endif
