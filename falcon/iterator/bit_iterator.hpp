#ifndef _FALCON_ITERATOR_BIT_ITERATOR_HPP
#define _FALCON_ITERATOR_BIT_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/bit/size.hpp>
#include <falcon/bit/bit_reference.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/default_or_type.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator, typename _T = typename std::iterator_traits<_Iterator>::pointer>
struct __bit_iterator_is_const
: false_type
{};

template <typename _Iterator, typename _T>
struct __bit_iterator_is_const<_Iterator, const _T *>
: true_type
{};

template <typename _Iterator>
struct __bit_iterator_is_const<_Iterator, void>
: true_type
{};

template<typename _Iterator, bool _IsConst = __bit_iterator_is_const<_Iterator>::value>
class bit_iterator;

namespace detail
{
	template <typename _Iterator, bool _IsConst>
	struct bit_base
	{
		struct __bit_reference_type {
			typedef falcon::basic_bit_reference<
				typename std::iterator_traits<_Iterator>::value_type
			> type;
		};

		typedef typename iterator_handler_types<
			bit_iterator<_Iterator, _IsConst>,
			_Iterator,
			use_default,
			bool,
			use_default,
			void,
			typename eval_if<_IsConst, use<bool>, __bit_reference_type>::type
		>::base base;
	};
}

template<typename _Iterator, bool _IsConst>
class bit_iterator
: public detail::bit_base<_Iterator, _IsConst>::base
{
	typedef typename detail::bit_base<_Iterator, _IsConst>::base __base;

	friend iterator_core_access;

	unsigned _M_offset;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::reference reference;
	typedef typename __base::difference_type difference_type;


	bit_iterator(iterator_type __x, unsigned __offset)
	: __base(__x), _M_offset(__offset)
	{}

	bit_iterator()
	: __base(), _M_offset(0)
	{}

	bit_iterator(const bit_iterator& __x)
	: __base(__x), _M_offset(__x._M_offset)
	{}

	unsigned int offset() const
	{ return _M_offset; }

	void offset(unsigned int __offset)
	{ _M_offset = __offset; }

private:
	typedef typename std::iterator_traits<_Iterator>::value_type __mask_t;
	static const unsigned _S_word_bit = bit::size<__mask_t>::value;

	__mask_t mask() const
	{ return static_cast<__mask_t>(1UL << _M_offset); }

	reference dereference(false_type)
	{ return reference(&*this->base_reference(), mask()); }

	reference dereference(false_type) const
	{ return reference(&*this->base_reference(), mask()); }

	reference dereference(true_type) const
	{ return !!(*this->base_reference() & mask()); }

	reference dereference()
	{ return dereference(falcon::integral_constant<bool, _IsConst>()); }

	reference dereference() const
	{ return dereference(falcon::integral_constant<bool, _IsConst>()); }

	void increment()
	{
		if (_M_offset++ == _S_word_bit - 1u)
		{
			_M_offset = 0;
			++this->base_reference();
		}
	}

	void decrement()
	{
		if (_M_offset-- == 0)
		{
			_M_offset = _S_word_bit - 1u;
			--this->base_reference();
		}
	}

	void advance(difference_type __i)
	{ move(__i); }

	void recoil(difference_type __i)
	{ move(-__i); }

	void move(difference_type __i)
	{
		difference_type __n = __i + _M_offset;
		this->base_reference() += __n / int(_S_word_bit);
		__n = __n % int(_S_word_bit);
		if (__n < 0)
		{
			__n += int(_S_word_bit);
			--this->base_reference();
		}
		_M_offset = static_cast<unsigned>(__n);
	}

	bool equal(const bit_iterator& other) const
	{ return _M_offset == other._M_offset
	&& this->base_reference() == other.base_reference(); }

	bool less(const bit_iterator& other) const
	{ return this->base_reference() < other.base_reference()
	|| (_M_offset < other._M_offset
	&& this->base_reference() == other.base_reference()); }
};

#if __cplusplus >= 201103L
template <typename _Iterator>
using const_bit_iterator = bit_iterator<_Iterator, true>;
#endif


template <typename _Iterator>
bit_iterator<_Iterator> make_bit_iterator(_Iterator x, unsigned offset)
{ return bit_iterator<_Iterator>(x, offset); }

template <typename _Iterator>
bit_iterator<_Iterator, true> make_const_bit_iterator(_Iterator x, unsigned offset)
{ return bit_iterator<_Iterator, true>(x, offset); }

}}

#endif
