#ifndef _FALCON_ITERATOR_NOT_ITERATOR_HPP
#define _FALCON_ITERATOR_NOT_ITERATOR_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
#endif
#include <iterator>
#include <falcon/preprocessor/incremental.hpp>
// #include <falcon/preprocessor/comparison.hpp>
#include <falcon/type_traits/difference.hpp>
#include <falcon/type_traits/add_const_reference.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace iterator {

template<typename _T>
struct not_iterator_traits
{
	typedef typename difference<_T>::type difference_type;
	typedef std::random_access_iterator_tag iterator_category;
	typedef _T value_type;
	typedef value_type& reference;
	typedef value_type* pointer;
};

template<typename _T>
struct not_iterator_traits<_T&>
{
	typedef typename difference<_T>::type difference_type;
	typedef std::random_access_iterator_tag iterator_category;
	typedef _T& value_type;
	typedef _T& reference;
	typedef _T* pointer;
};

struct not_iterator_comparison_less_tag {};
struct not_iterator_comparison_equal_to_tag {};

template<typename _T, typename _ComparisonTag = not_iterator_comparison_equal_to_tag>
struct not_iterator
{
private:
	typedef not_iterator_traits<_T> __traits;

public:
	typedef typename __traits::difference_type difference_type;
	typedef typename __traits::iterator_category iterator_category;
	typedef typename __traits::value_type value_type;
	typedef typename __traits::reference reference;
	typedef typename __traits::pointer pointer;

private:
	_T _value;

public:
	CPP_CONSTEXPR not_iterator()
	: _value()
	{}

	CPP_CONSTEXPR not_iterator(const _T& value)
	: _value(value)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _U, class _Enable = typename
	std::enable_if<std::is_reference<_T>::value && std::is_convertible<_U, _T>::value>::type>
	constexpr not_iterator(_U&& value)
	: _value(std::forward<_U>(value))
	{}
#endif

	not_iterator& operator=(const _T& other)
	{
		_value = other;
		return *this;
	}

	reference operator*()
	{ return _value; }
	typename not_iterator_traits<const _T>::reference operator*() const
	{ return _value; }

	pointer operator->()
	{ return &_value; }
	typename not_iterator_traits<const _T>::pointer operator->() const
	{ return &_value; }

// 	operator _T& ()
// 	{ return _value; }
// 	operator const _T& () const
// 	{ return _value; }

	FALCON_MEMBER_INCREMENT(not_iterator, ++_value)
	FALCON_MEMBER_DECREMENT(not_iterator, --_value)

// 	FALCON_MEMBER_COMPARISON_ALL_OPERATOR(value_type, _value)
// 	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(not_iterator, _value, other._value)
};

template<typename _T, typename _ComparisonTag>
struct not_iterator<const _T, _ComparisonTag>
{
private:
	typedef not_iterator_traits<const _T> __traits;

public:
	typedef typename __traits::difference_type difference_type;
	typedef typename __traits::iterator_category iterator_category;
	typedef typename __traits::value_type value_type;
	typedef typename __traits::reference reference;
	typedef typename __traits::pointer pointer;

private:
	_T _value;

public:
	CPP_CONSTEXPR not_iterator()
	: _value()
	{}

	CPP_CONSTEXPR not_iterator(const _T& value)
	: _value(value)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _U, class _Enable = typename
	std::enable_if<std::is_convertible<_U, _T>::value>::type>
	constexpr not_iterator(_U&& value)
	: _value(std::forward<_U>(value))
	{}
#endif

	not_iterator& operator=(const _T& other)
	{
		_value = other;
		return *this;
	}

	reference operator*() const
	{ return _value; }

	pointer operator->() const
	{ return &_value; }

// 	operator _T& ()
// 	{ return _value; }
// 	operator const _T& () const
// 	{ return _value; }

	FALCON_MEMBER_INCREMENT(not_iterator, ++_value)
	FALCON_MEMBER_DECREMENT(not_iterator, --_value)

// 	FALCON_MEMBER_COMPARISON_ALL_OPERATOR(value_type, _value)
// 	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(not_iterator, _value, other._value)
};

template <typename _T, typename _ComparisonTag>
CPP_CONSTEXPR typename not_iterator<_T, _ComparisonTag>::difference_type
operator-(const not_iterator<_T, _ComparisonTag>& a,
		  const not_iterator<_T, _ComparisonTag>& b)
{
	return *a - *b;
}

template <typename _T, typename _ComparisonTag>
CPP_CONSTEXPR not_iterator<_T, _ComparisonTag>
operator+(const not_iterator<_T, _ComparisonTag>& a, int next)
{
	return {*a + next};
}

template <typename _T, typename _ComparisonTag>
not_iterator<_T, _ComparisonTag>&
operator+=(not_iterator<_T, _ComparisonTag>& a, int next)
{
	*a += next;
	return a;
}

template <typename _T, typename _ComparisonTag>
not_iterator<_T, _ComparisonTag>&
operator-=(not_iterator<_T, _ComparisonTag>& a, int prev)
{
	*a -= prev;
	return a;
}

template <typename _T>
CPP_CONSTEXPR bool operator==(
	const not_iterator<_T, not_iterator_comparison_equal_to_tag>& a,
	const not_iterator<_T, not_iterator_comparison_equal_to_tag>& b)
{
	return *a == *b;
}

template <typename _T>
CPP_CONSTEXPR bool operator==(
	const not_iterator<_T, not_iterator_comparison_less_tag>& a,
	const not_iterator<_T, not_iterator_comparison_less_tag>& b)
{
	return !(*a < *b);
}

template <typename _T, typename _ComparisonTag>
CPP_CONSTEXPR bool operator!=(const not_iterator<_T, _ComparisonTag>& a,
							  const not_iterator<_T, _ComparisonTag>& b)
{
	return !(a == b);
}

template <typename _T, typename _ComparisonTag>
CPP_CONSTEXPR not_iterator<_T, _ComparisonTag> make_not_iterator(const _T& value)
{
	return not_iterator<_T, _ComparisonTag>(value);
}

template <typename _T, typename _ComparisonTag>
CPP_CONSTEXPR not_iterator<const _T> make_cnot_iterator(const _T& value)
{
	return not_iterator<const _T>(value);
}

}
}

#endif