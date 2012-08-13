#ifndef _FALCON_ITERATOR_BIT_ITERATOR_ITERATOR_HPP
#define _FALCON_ITERATOR_BIT_ITERATOR_ITERATOR_HPP

#include <falcon/preprocessor/incremental.hpp>
#include <falcon/bit/edge_bit.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>
#include <falcon/endian.hpp>

namespace falcon {

namespace iterator {

template<typename _Iterator>
class __bit_iterator_iterator_base
{
	typedef __bit_iterator_iterator_base<_Iterator> self_type;

private:
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _Iterator iterator_type;
	typedef typename iterator_traits::value_type value_type;

protected:
	_Iterator _iterator;
	/*value_type*/long _mask;

public:
	__bit_iterator_iterator_base(_Iterator data_iterator, const value_type& __mask)
	: _iterator(data_iterator)
	, _mask(__mask)
	{}

	self_type& operator=(const self_type& other)
	{
		_iterator == other._iterator;
		_mask == other._mask;
		return *this;
	}

	const _Iterator& iterator() const
	{ return _iterator; }

	value_type operator*() const
	{ return static_cast<value_type>((*_iterator) & _mask); }

	bool operator==(const self_type& other) const
	{ return _iterator == other._iterator && _mask == other._mask; }

	bool operator!=(const self_type& other) const
	{ return !(operator==(other)); }

	bool operator==(const _Iterator& other) const
	{ return _iterator == other._iterator; }

	bool operator!=(const _Iterator& other) const
	{ return !(operator==(other)); }

	template<typename _BitIterator>
	bool operator==(const __bit_iterator_iterator_base<_BitIterator>& other) const
	{ return _iterator == other._iterator && _mask == other._mask; }

	template<typename _BitIterator>
	bool operator!=(const __bit_iterator_iterator_base<_BitIterator>& other) const
	{ return !(operator==(other)); }

	bool operator<(const self_type& other) const
	{ return _iterator < other._iterator || less_bit_endian(other._mask, _mask); }

	bool operator<(const _Iterator& other) const
	{ return _iterator < other._iterator; }

	template<typename _BitIterator>
	bool operator<(const __bit_iterator_iterator_base<_BitIterator>& other) const
	{ return _iterator < other._iterator; }

	template<typename _BitIterator>
	bool operator&&(const __bit_iterator_iterator_base<_BitIterator>& other) const
	{ return operator*() && *other; }

	template<typename _BitIterator>
	bool operator||(const __bit_iterator_iterator_base<_BitIterator>& other) const
	{ return operator*() || *other; }

	inline void zero()
	{ *_iterator &= ~_mask; }

	inline void one()
	{ *_iterator |= _mask; }

	inline void set_bit(bool v)
	{ v ? one() : zero(); }

	template<typename _BitIterator>
	inline void set_bit(const __bit_iterator_iterator_base<_BitIterator>& other)
	{ set_bit(*other); }

	template<typename _BitIterator>
	inline void swap(__bit_iterator_iterator_base<_BitIterator>& other)
	{
		bool v = *other;
		other.set_bit(*this);
		set_bit(v);
	}

	const /*value_type*/long& mask() const
	{ return _mask; }
};

template<typename _Iterator>
class bit_iterator_iterator : public __bit_iterator_iterator_base<_Iterator>
{
	typedef bit_iterator_iterator<_Iterator> self_type;
	typedef __bit_iterator_iterator_base<_Iterator> base_type;
	using base_type::_mask;
	using base_type::_iterator;

public:
	typedef _Iterator iterator_type;
	typedef typename base_type::value_type value_type;

public:
	static const value_type default_mask = left_bit<value_type>::value;

public:
	bit_iterator_iterator(_Iterator data_iterator, const value_type& __mask = default_mask)
	: base_type(data_iterator, __mask)
	{}

	FALCON_MEMBER_INCREMENT(self_type,
							if (_mask == right_bit<value_type>::value){
								++_iterator;
								_mask = default_mask;
							} else {
								_mask >>= 1;
							})
	FALCON_MEMBER_DECREMENT(self_type,
							if (_mask == left_bit<value_type>::value){
								--_iterator;
								_mask = right_bit<value_type>::value;
							} else {
								_mask <<= 1;
							})
};

template<typename _Iterator>
class reverse_bit_iterator_iterator : public __bit_iterator_iterator_base<_Iterator>
{
	typedef reverse_bit_iterator_iterator<_Iterator> self_type;
	typedef __bit_iterator_iterator_base<_Iterator> base_type;
	using base_type::_mask;
	using base_type::_iterator;

public:
	typedef _Iterator iterator_type;
	typedef typename base_type::value_type value_type;

public:
	static const value_type default_mask = right_bit<value_type>::value;

public:
	reverse_bit_iterator_iterator(_Iterator data_iterator, const value_type& __mask = default_mask)
	: base_type(data_iterator, __mask)
	{}

	FALCON_MEMBER_INCREMENT(self_type,
							if (_mask == left_bit<value_type>::value){
								++_iterator;
								_mask = default_mask;
							} else {
								_mask <<= 1;
							})
	FALCON_MEMBER_DECREMENT(self_type,
							if (_mask == right_bit<value_type>::value){
								--_iterator;
								_mask = left_bit<value_type>::value;
							} else {
								_mask >>= 1;
							})
};

}

}

#endif