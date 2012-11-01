#ifndef _FALCON_ITERATOR_BIT_ITERATOR_HPP
#define _FALCON_ITERATOR_BIT_ITERATOR_HPP

#include <falcon/iterator/detail/handler_iterator.hpp>
#include <falcon/bit/bit_size.hpp>
#include <falcon/bit/bit_reference.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
namespace iterator {
	template <typename _Iterator, typename _T = typename std::iterator_traits<_Iterator>::pointer>
	struct __bit_iterator_is_const
	: true_type
	{};

	template <typename _Iterator, typename _T>
	struct __bit_iterator_is_const<_Iterator, const _T *>
	: false_type
	{};

	template <typename _Iterator, bool _IsConst = false>
	class bit_iterator;

	template <typename _Iterator>
	struct __bit_iterator_traits_base
	: std::iterator_traits<
		std::iterator<
			typename std::iterator_traits<_Iterator>::iterator_category,
			bool
		>
	>
	{};
}}

namespace std
{
	template <typename _Iterator>
	struct iterator_traits< ::falcon::iterator::bit_iterator<_Iterator, false> >
	: falcon::iterator::__bit_iterator_traits_base<_Iterator>
	{
		typedef falcon::basic_bit_reference<
			typename iterator_traits<_Iterator>::value_type
		> reference;
		typedef reference* pointer;
	};

	template <typename _Iterator>
	struct iterator_traits< ::falcon::iterator::bit_iterator<_Iterator, true> >
	: falcon::iterator::__bit_iterator_traits_base<_Iterator>
	{
		typedef bool        reference;
		typedef bool        const_reference;
		typedef const bool* pointer;
	};
}

namespace falcon {
namespace iterator {

template<typename _Iterator, bool _IsConst>
struct __bit_iterator_traits
: detail::handler_iterator_trait<bit_iterator<_Iterator, _IsConst>, _Iterator>
{
	typedef bit_iterator<_Iterator, _IsConst> __bit_iterator;
	typedef detail::handler_iterator_trait<__bit_iterator, _Iterator> __base;
	typedef typename std::iterator_traits<_Iterator>::value_type __value_type;
	typedef typename __base::reference __reference;
	static const unsigned _S_word_bit = bit_size<__value_type>::value;

	static __reference dereference(const __bit_iterator& it)
	{ return __reference(&*it._M_current, static_cast<__value_type>(1UL << it._M_offset)); }

	static __reference dereference(__bit_iterator& it)
	{ return __reference(&*it._M_current, static_cast<__value_type>(1UL << it._M_offset)); }

	static void next(__bit_iterator& it)
	{
		if (it._M_offset++ == _S_word_bit - 1u)
		{
			it._M_offset = 0;
			++it._M_current;
		}
	}

	static void next(__bit_iterator& it, int n)
	{ incr(it, n); }

	static __bit_iterator next(const __bit_iterator& it, int n, int)
	{
		__bit_iterator ret(it);
		incr(ret, n);
		return ret;
	}

	static void prev(__bit_iterator& it)
	{
		if (it._M_offset-- == 0)
		{
			it._M_offset = _S_word_bit - 1u;
			--it._M_current;
		}
	}

	static void prev(__bit_iterator& it, int n)
	{ incr(it, -n); }

	static __bit_iterator prev(const __bit_iterator& it, int n, int)
	{
		__bit_iterator ret(it);
		incr(ret, -n);
		return ret;
	}

	static void incr(__bit_iterator& it, ptrdiff_t __i)
	{
		typename __base::difference_type __n = __i + it._M_offset;
		it._M_current += __n / int(_S_word_bit);
		__n = __n % int(_S_word_bit);
		if (__n < 0)
		{
			__n += int(_S_word_bit);
			--it._M_current;
		}
		it._M_offset = static_cast<unsigned>(__n);
	}

	static bool eq(const __bit_iterator& a, const __bit_iterator& b)
	{ return a._M_current == b._M_current && a._M_offset == b._M_offset; }

	static bool lt(const __bit_iterator& a, const __bit_iterator& b)
	{ return a._M_current < b._M_current || (a._M_current == b._M_current && a._M_offset < b._M_offset); }
};

template<typename _Iterator, bool _IsConst>
class bit_iterator
: public detail::handler_iterator<
	bit_iterator<_Iterator, _IsConst>,
	_Iterator,
	__bit_iterator_traits<_Iterator, _IsConst>
>
{
	typedef detail::handler_iterator<
		bit_iterator<_Iterator, _IsConst>,
		_Iterator,
		__bit_iterator_traits<_Iterator, _IsConst>
	> __base;

public:
	unsigned _M_offset;

	typedef typename __base::iterator_type iterator_type;


	bit_iterator(iterator_type __x, unsigned offset)
	: __base(__x), _M_offset(offset)
	{}

	bit_iterator()
	: __base(), _M_offset(0)
	{}

	bit_iterator(const bit_iterator& __x)
	: __base(__x), _M_offset(__x._M_offset)
	{}
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
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