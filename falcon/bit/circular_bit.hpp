#ifndef _FALCON_BIT_CIRCULAR_BIT_HPP
#define _FALCON_BIT_CIRCULAR_BIT_HPP

#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/bit/first_bit.hpp>
#include <falcon/bit/last_bit.hpp>

namespace falcon {

template <typename _T>
class circular_bit;

template <typename _T>
class reverse_circular_bit;

template <typename _T>
class __circular_bit
{
	typedef __circular_bit<_T> self_type;
	friend class circular_bit<_T>;
	friend class reverse_circular_bit<_T>;

public:
	typedef _T value_type;

private:
	/*value_type*/ long _mask;

public:
	__circular_bit(const value_type& mask)
	: _mask(mask)
	{}

	__circular_bit(const self_type& other)
	: _mask(other._mask)
	{}

	self_type& operator=(const self_type& other)
	{
		_mask == other._mask;
		return *this;
	}

	const /*value_type*/long& operator*() const
	{ return _mask; }

	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(self_type, _mask, other._mask)
};

template <typename _T>
class circular_bit : public __circular_bit<_T>
{
	typedef circular_bit<_T> self_type;
	typedef __circular_bit<_T> base_type;
	using __circular_bit<_T>::_mask;

public:
	typedef typename base_type::value_type value_type;

public:
	circular_bit()
	: base_type(value_type(left_bit<value_type>::value))
	{}

	circular_bit(const value_type& mask)
	: base_type(first_bit<>(mask))
	{}

	FALCON_MEMBER_INCREMENT(self_type,
							if (_mask == right_bit<value_type>::value)
								_mask = left_bit<value_type>::value;
							else
								_mask >>= 1;
						   )
	FALCON_MEMBER_DECREMENT(self_type,
							if (_mask == left_bit<value_type>::value)
								_mask = right_bit<value_type>::value;
							else
								_mask <<= 1;
							)

	bool reset()
	{ return _mask = left_bit<value_type>::value; }
};

template <typename _T>
class reverse_circular_bit : public __circular_bit<_T>
{
	typedef reverse_circular_bit<_T> self_type;
	typedef __circular_bit<_T> base_type;
	using __circular_bit<_T>::_mask;

public:
	typedef typename base_type::value_type value_type;

public:
	reverse_circular_bit()
	: base_type(value_type(right_bit<value_type>::value))
	{}

	reverse_circular_bit(const value_type& mask)
	: base_type(last_bit<>(mask))
	{}

	FALCON_MEMBER_INCREMENT(self_type,
							if (_mask == left_bit<value_type>::value)
								_mask = right_bit<value_type>::value;
							else
								_mask <<= 1;
							)
	FALCON_MEMBER_DECREMENT(self_type,
							if (_mask == right_bit<value_type>::value)
								_mask = left_bit<value_type>::value;
							else
								_mask >>= 1;
							)

	bool reset()
	{ return _mask = right_bit<value_type>::value; }
};

}

#endif