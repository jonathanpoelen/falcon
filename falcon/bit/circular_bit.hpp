#ifndef FALCON_BIT_CIRCULAR_BIT_HPP
#define FALCON_BIT_CIRCULAR_BIT_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/unqualified.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/bit/right.hpp>
#include <falcon/bit/left.hpp>

namespace falcon {
namespace _aux {

template <class Class, class T, bool IsReverse = false>
class circular_bit
{
public:
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<T>::type value_type;

private:
	typedef typename unqualified<value_type>::type unqualified_type;
	static const unqualified_type s_left = bit::left<unqualified_type>::value;
	static const unqualified_type s_right = bit::right<unqualified_type>::value;

private:
	value_type _mask;

public:
	circular_bit()
	: _mask(IsReverse ? s_right : s_left)
	{}

	circular_bit(const value_type& mask)
	: _mask(mask)
	{}

	circular_bit(const circular_bit& other)
	: _mask(other._mask)
	{}

	circular_bit& operator=(const circular_bit& other)
	{
		_mask == other._mask;
		return *this;
	}

	const value_type& operator*() const
	{ return _mask; }

	const value_type& get() const
	{ return _mask; }

private:
	void move(false_type)
	{
		if (_mask == s_left)
			_mask = s_right;
		else
			_mask = static_cast<T>(_mask << 1);
	}

	void move(true_type)
	{
		if (_mask == s_right)
			_mask = s_left;
		else
			_mask = static_cast<T>(_mask >> 1);
	}

public:
	Class& operator++()
	{
		move(integral_constant<bool, !IsReverse>());
		return static_cast<Class&>(*this);
	}

	Class operator++(int)
	{
		Class tmp(static_cast<Class&>(*this));
		return ++tmp;
	}

	Class& operator--()
	{
		move(integral_constant<bool, IsReverse>());
		return static_cast<Class&>(*this);
	}

	Class operator--(int)
	{
		Class tmp(static_cast<Class&>(*this));
		return --tmp;
	}

	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(circular_bit, _mask, other._mask)

	void reset()
	{ _mask = IsReverse ? s_right : s_left; }
};

}

template <class T>
class basic_circular_bit
: public _aux::circular_bit<basic_circular_bit<T>, T>
{
  typedef _aux::circular_bit<basic_circular_bit<T>, T> base_type;

public:
	typedef typename base_type::value_type value_type;

public:
	basic_circular_bit()
	: base_type()
	{}

	basic_circular_bit(const value_type& mask)
	: base_type(mask)
	{}
};

template <class T>
class basic_reverse_circular_bit
: public _aux::circular_bit<basic_reverse_circular_bit<T>, T, true>
{
  typedef _aux::circular_bit<basic_reverse_circular_bit<T>, T, true> base_type;

public:
	typedef typename base_type::value_type value_type;

public:
	basic_reverse_circular_bit()
	: base_type()
	{}

	basic_reverse_circular_bit(const value_type& mask)
	: base_type(mask)
	{}
};

typedef basic_circular_bit<unsigned> u_circular_bit;
typedef basic_reverse_circular_bit<unsigned> reverse_u_circular_bit;
typedef basic_circular_bit<unsigned long> ul_circular_bit;
typedef basic_reverse_circular_bit<unsigned long> reverse_ul_circular_bit;
#if __cplusplus >= 201103L
typedef basic_circular_bit<unsigned long long> ull_circular_bit;
typedef basic_reverse_circular_bit<unsigned long long> reverse_ull_circular_bit;
#endif

}

#endif
