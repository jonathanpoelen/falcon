#ifndef _FALCON_ITERATOR_BIT_ITERATOR_HPP
#define _FALCON_ITERATOR_BIT_ITERATOR_HPP

#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/bit/edge_bit.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>
#include <falcon/endian.hpp>

namespace falcon {

namespace iterator {

template<typename _T>
class __bit_iterator_base
{
	typedef __bit_iterator_base<_T> self_type;

public:
	typedef _T value_type;

protected:
	/*value_type*/ long _mask;

public:
	__bit_iterator_base()
	: _mask()
	{}

	__bit_iterator_base(const /*value_type*/long& mask)
	: _mask(mask)
	{}

	self_type& operator=(const self_type& other)
	{
		_mask = other._mask;
		return *this;
	}

	self_type& operator=(const value_type& other)
	{
		_mask = other;
		return *this;
	}

	const /*value_type*/long& operator*() const
	{ return _mask; }

	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(self_type, _mask, other._mask)

	template<typename _BitIterator>
	bool operator&&(const __bit_iterator_base<_BitIterator>& other) const
	{ return operator*() && *other; }

	template<typename _BitIterator>
	bool operator||(const __bit_iterator_base<_BitIterator>& other) const
	{ return operator*() || *other; }

	/*value_type*/long operator~() const
	{ return ~_mask; }

	bool valid() const
	{ return _mask; }
};

template<typename _T>
class bit_iterator : public __bit_iterator_base<_T>
{
	typedef bit_iterator<_T> self_type;
	typedef __bit_iterator_base<_T> base_type;
	using base_type::_mask;

public:
	typedef typename base_type::value_type value_type;
	//static const value_type begin = right_bit<value_type>::value;
	//static const value_type end = left_bit<value_type>::value;
	static const value_type first_value = left_bit<value_type>::value;
	static const value_type last_value = 0;

public:
	bit_iterator(const value_type& mask)
	: base_type(mask)
	{}

	bit_iterator()
	: base_type()
	{}

	FALCON_MEMBER_INCREMENT(self_type, _mask >>= 1)
	FALCON_MEMBER_DECREMENT(self_type, _mask <<= 1)
};

template<typename _T>
class reverse_bit_iterator : public __bit_iterator_base<_T>
{
	typedef reverse_bit_iterator<_T> self_type;
	typedef __bit_iterator_base<_T> base_type;
	using base_type::_mask;

public:
	typedef typename base_type::value_type value_type;
	//static const value_type begin = left_bit<value_type>::value;
	//static const value_type end = right_bit<value_type>::value;
	static const value_type first_value = right_bit<value_type>::value;
	static const value_type last_value = 0;

public:
	reverse_bit_iterator(/*value_type*/long mask)
	: base_type(mask)
	{}

	reverse_bit_iterator()
	: base_type()
	{}

	FALCON_MEMBER_INCREMENT(self_type, _mask <<= 1)
	FALCON_MEMBER_DECREMENT(self_type, _mask >>= 1)};

}

}

#endif