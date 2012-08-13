#ifndef _FALCON_RANGE_RANGE_MODIFIER_HPP
#define _FALCON_RANGE_RANGE_MODIFIER_HPP

#include <falcon/container/range_access.hpp>

namespace falcon {

/**
 * \brief Wrapper for use operators affect a value in a container
 *
 * make_range_modifier(container) += 8;
 * make_range(first, last).modifier() -= 7;
 */
template<typename _Range>
struct range_modifier
{
	_Range& _M_range;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	typedef decltype(begin(_M_range)) iterator;
#else
	typedef typename range_access_iterator<_Range>::iterator iterator;
#endif

	range_modifier(_Range& range)
	: _M_range(range)
	{}

	template<typename _T>
	range_modifier<_Range>& operator=(const _T& v)
	{
		for (iterator first = begin(_M_range), last = end(_M_range); first != last; ++first)
			*first = v;
		return *this;
	}

	template<typename _Functor>
	range_modifier& unary(_Functor func)
	{
		for (iterator first = begin(_M_range), last = end(_M_range); first != last; ++first)
			func(*first);
		return *this;
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _Functor, typename _T>
	range_modifier& binary(_Functor func, _T&& v)
	{
		for (iterator first = begin(_M_range), last = end(_M_range); first != last; ++first)
			func(*first, v);
		return *this;
	}
#else
	template<typename _Functor, typename _T>
	range_modifier& binary(_Functor func, _T& v)
	{
		for (iterator first = begin(_M_range), last = end(_M_range); first != last; ++first)
			func(*first, v);
		return *this;
	}
	template<typename _Functor, typename _T>
	range_modifier& binary(_Functor func, const _T& v)
	{
		for (iterator first = begin(_M_range), last = end(_M_range); first != last; ++first)
			func(*first, v);
		return *this;
	}
#endif

};

template<typename _Container>
range_modifier<_Container> make_range_modifier(_Container& container)
{
	return range_modifier<_Container>(container);
}

#define _FALCON_CREATE_RANGE_FUNCTION_OPERATOR(op)\
	template<typename _Range, typename _T>\
	range_modifier<_Range> operator op(range_modifier<_Range> range, const _T& v)\
	{\
		for (typename range_modifier<_Range>::iterator first = begin(range._M_range), last = end(range._M_range); first != last; ++first)\
			*first op v;\
		return range;\
	}

_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(+=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(-=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(*=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(/=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(|=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(&=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(^=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(%=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(>>=)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(<<=)

#undef _FALCON_CREATE_RANGE_FUNCTION_OPERATOR

#define _FALCON_CREATE_RANGE_FUNCTION_OPERATOR(op)\
	template<typename _Range>\
	range_modifier<_Range> operator op(range_modifier<_Range> range)\
	{\
		for (typename range_modifier<_Range>::iterator first = begin(range._M_range), last = end(range._M_range); first != last; ++first)\
			op(*first);\
		return range;\
	}\
	template<typename _Range>\
	range_modifier<_Range> operator op(range_modifier<_Range> range, int)\
	{\
		for (typename range_modifier<_Range>::iterator first = begin(range._M_range), last = end(range._M_range); first != last; ++first)\
			op(*first);\
		return range;\
	}

_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(++)
_FALCON_CREATE_RANGE_FUNCTION_OPERATOR(--)

#undef _FALCON_CREATE_RANGE_FUNCTION_OPERATOR

template<typename _Range, typename _T>
bool operator==(range_modifier<_Range> range, const _T v)
{
	for (typename range_modifier<_Range>::iterator first = begin(range._M_range), last = end(range._M_range); first != last; ++first)
	{
		if (*first != v)
			return false;
	}
	return true;
}

template<typename _Range, typename _T>
bool operator<(range_modifier<_Range> range, const _T v)
{
	for (typename range_modifier<_Range>::iterator first = begin(range._M_range), last = end(range._M_range); first != last; ++first)
	{
		if (*first >= v)
			return false;
	}
	return true;
}

template<typename _Range, typename _T>
bool operator>(range_modifier<_Range> range, const _T v)
{
	for (typename range_modifier<_Range>::iterator first = begin(range._M_range), last = end(range._M_range); first != last; ++first)
	{
		if (*first <= v)
			return false;
	}
	return true;
}

template<typename _Range, typename _T>
bool operator!=(range_modifier<_Range> range, const _T v)
{ return !(range == v); }

template<typename _Range, typename _T>
bool operator<=(range_modifier<_Range> range, const _T v)
{ return !(range > v); }

template<typename _Range, typename _T>
bool operator>=(range_modifier<_Range> range, const _T v)
{ return !(range < v); }

}

#endif
