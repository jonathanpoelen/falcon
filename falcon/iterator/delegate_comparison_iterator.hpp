#ifndef _FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP
#define _FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP

#include <falcon/iterator/detail/handler_iterator.hpp>

namespace falcon {
namespace iterator {
	template <typename _Iterator, typename _ComparisonIterator>
	class delegate_comparison_iterator;
}}

namespace std
{
	template <typename _Iterator, typename _Proxy>
	struct iterator_traits<
		::falcon::iterator::delegate_comparison_iterator<_Iterator, _Proxy>
	> : iterator_traits<_Iterator>
	{};
}

namespace falcon {
namespace iterator {

template<typename>
class __delegate_comparison_iterator_traits;

template<typename _Iterator, typename _ComparisonIterator>
struct __delegate_comparison_iterator_traits<
	delegate_comparison_iterator<_Iterator, _ComparisonIterator>
> : detail::handler_iterator_trait<
	delegate_comparison_iterator<_Iterator, _ComparisonIterator>,
	_Iterator
>
{
	typedef delegate_comparison_iterator<_Iterator, _ComparisonIterator> __iterator;

	static bool eq(const __iterator& a, const __iterator& b)
	{ return a.comparison_iterator() == b.comparison_iterator(); }

	static bool lt(const __iterator& a, const __iterator& b)
	{ return a.comparison_iterator() < b.comparison_iterator(); }

	static void next(__iterator& it)
	{ ++it._M_current; ++it.comparison_iterator(); }

	static void next(__iterator& it, int n)
	{ it._M_current += n; it.comparison_iterator() += n; }

	static __iterator next(const __iterator& it, int n, int)
	{ return __iterator(it._M_current + n, it.comparison_iterator() + n); }

	static void prev(__iterator& it)
	{ --it._M_current; --it.comparison_iterator(); }

	static void prev(__iterator& it, int n)
	{ it._M_current -= n; it.comparison_iterator() -= n; }

	static __iterator prev(const __iterator& it, int n, int)
	{ return __iterator(it._M_current - n, it.comparison_iterator() - n); }
};


template <typename _Iterator, typename _ComparisonIterator>
class delegate_comparison_iterator
: public detail::handler_iterator<
	delegate_comparison_iterator<_Iterator, _ComparisonIterator>,
	_Iterator,
	__delegate_comparison_iterator_traits<
		delegate_comparison_iterator<_Iterator, _ComparisonIterator>
	>
>
{
	typedef detail::handler_iterator<
		delegate_comparison_iterator<_Iterator, _ComparisonIterator>,
		_Iterator,
		__delegate_comparison_iterator_traits<
			delegate_comparison_iterator<_Iterator, _ComparisonIterator>
		>
	> __base;

	_ComparisonIterator _comparison_iterator;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef _ComparisonIterator comparison_iterator_type;

public:
	delegate_comparison_iterator()
	: __base()
	, _comparison_iterator()
	{}

	explicit delegate_comparison_iterator(comparison_iterator_type __comparison_iterator)
	: __base()
	, _comparison_iterator(__comparison_iterator)
	{}

	explicit delegate_comparison_iterator(iterator_type __x, const comparison_iterator_type& __comparison_iterator)
	: __base(__x)
	, _comparison_iterator(__comparison_iterator)
	{}

	delegate_comparison_iterator(const delegate_comparison_iterator& __x)
	: __base(__x._M_current)
	, _comparison_iterator(__x._comparison_iterator)
	{}

	using __base::operator=;

	const comparison_iterator_type& comparison_iterator() const
	{ return _comparison_iterator; }

	comparison_iterator_type& comparison_iterator()
	{ return _comparison_iterator; }
};

template <typename _Iterator, typename _ComparisonIterator>
iterator::delegate_comparison_iterator<_Iterator, _ComparisonIterator> make_delegate_comparison_iterator(const _Iterator& begin, const _ComparisonIterator& compare)
{ return iterator::delegate_comparison_iterator<_Iterator, _ComparisonIterator>(begin, compare); }

}}

#endif