#ifndef _FALCON_BIT_CIRCULAR_BIT_HPP
#define _FALCON_BIT_CIRCULAR_BIT_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/invalid_type.hpp>
#include <falcon/type_traits/unqualified.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/bit/right_bit.hpp>
#include <falcon/bit/left_bit.hpp>

namespace falcon {

template <typename _Class, typename _T, bool _IsReverse = false>
class __circular_bit
{
public:
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<_T>::type value_type;

private:
	typedef typename unqualified<value_type>::type __unqualified_type;
	static const __unqualified_type _S_left = left_bit<__unqualified_type>::value;
	static const __unqualified_type _S_right = right_bit<__unqualified_type>::value;

private:
	value_type _mask;

public:
	__circular_bit()
	: _mask(_IsReverse ? _S_right : _S_left)
	{}

	__circular_bit(const value_type& mask)
	: _mask(mask)
	{}

	__circular_bit(const __circular_bit& other)
	: _mask(other._mask)
	{}

	__circular_bit& operator=(const __circular_bit& other)
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
		if (_mask == _S_left)
			_mask = _S_right;
		else
			_mask = static_cast<_T>(_mask << 1);
	}

	void move(true_type)
	{
		if (_mask == _S_right)
			_mask = _S_left;
		else
			_mask = static_cast<_T>(_mask >> 1);
	}

public:
	_Class& operator++()
	{
		move(integral_constant<bool, !_IsReverse>());
		return static_cast<_Class&>(*this);
	}

	_Class operator++(int)
	{
		_Class tmp(static_cast<_Class&>(*this));
		return ++tmp;
	}

	_Class& operator--()
	{
		move(integral_constant<bool, _IsReverse>());
		return static_cast<_Class&>(*this);
	}

	_Class operator--(int)
	{
		_Class tmp(static_cast<_Class&>(*this));
		return --tmp;
	}

	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(__circular_bit, _mask, other._mask)

	void reset()
	{ _mask = _IsReverse ? _S_right : _S_left; }
};

template <typename _T>
class basic_circular_bit
: public __circular_bit<basic_circular_bit<_T>, _T>
{
	typedef __circular_bit<basic_circular_bit<_T>, _T> __base;

public:
	typedef typename __base::value_type value_type;

public:
	basic_circular_bit()
	: __base()
	{}

	basic_circular_bit(const value_type& mask)
	: __base(mask)
	{}
};

template <typename _T>
class basic_reverse_circular_bit
: public __circular_bit<basic_reverse_circular_bit<_T>, _T, true>
{
	typedef __circular_bit<basic_reverse_circular_bit<_T>, _T, true> __base;

public:
	typedef typename __base::value_type value_type;

public:
	basic_reverse_circular_bit()
	: __base()
	{}

	basic_reverse_circular_bit(const value_type& mask)
	: __base(mask)
	{}
};

typedef basic_circular_bit<unsigned long> circular_bit;
typedef basic_reverse_circular_bit<unsigned long> reverse_circular_bit;

}

#endif