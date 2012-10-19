#ifndef _FALCON_ITERATOR_PSEUDO_ITERATOR_HPP
#define _FALCON_ITERATOR_PSEUDO_ITERATOR_HPP

#include <iterator>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/preprocessor/move.hpp>
#include <falcon/c++/reference.hpp>

namespace falcon {

namespace iterator {

template<typename _T>
struct pseudo_iterator
{
	typedef _T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef std::random_access_iterator_tag iterator_category;

private:
	typedef pseudo_iterator<_T> self_type;

private:
	value_type _value;

public:
	pseudo_iterator()
	{}

	pseudo_iterator(const value_type& value)
	: _value(value)
	{}

	pseudo_iterator(const self_type& other)
	: _value(other._value)
	{}

	self_type& operator=(const value_type& value)
	{
		_value = _value;
		return *this;
	}

	self_type& operator=(const self_type& other)
	{
		_value = other._value;
		return *this;
	}

	FALCON_MEMBER_GETTER(value_type, operator*, _value)
	FALCON_MEMBER_GETTER(pointer, operator->, &_value)

	FALCON_CAST_GETTER(value_type, _value)

	inline self_type& operator++()
	{ return *this; }
	inline self_type& operator++(int)
	{ return *this; }
	inline self_type& operator--()
	{ return *this; }
	inline self_type& operator--(int)
	{ return *this; }
	template<typename _I>
	inline self_type& operator+=(const _I&)
	{ return *this; }
	template<typename _I>
	inline self_type& operator-=(const _I&)
	{ return *this; }

	inline bool operator == (const self_type & ) const
	{ return false; }

	inline bool operator != (const self_type & ) const
	{ return true; }
};

template <typename _T>
pseudo_iterator<_T> make_proxy_iterator(CPP_RVALUE_OR_CONST_REFERENCE(_T) value) {
	return pseudo_iterator<_T>(FALCON_FORWARD(_T, value));
}

}

}

#endif