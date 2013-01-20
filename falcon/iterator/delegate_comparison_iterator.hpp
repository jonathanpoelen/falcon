#ifndef _FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP
#define _FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator, typename _ComparisonIterator,
	typename _Tp = use_default,
	typename _Category = use_default,
	typename _Reference = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default
>
class delegate_comparison_iterator;

namespace detail {

	template <typename _Iterator, typename _ComparisonIterator, typename _Tp,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct delegate_comparison_base
	{
		typedef typename iterator_handler_types<
			delegate_comparison_iterator<_Iterator, _ComparisonIterator,
				_Tp, _Category, _Reference, _Distance, _Pointer>,
			_Iterator,
			_Category,
			_Tp,
			_Distance,
			_Pointer,
			_Reference
		>::base base;
	};

}

template <typename _Iterator, typename _ComparisonIterator,
	typename _Tp,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class delegate_comparison_iterator
: public detail::delegate_comparison_base<_Iterator, _ComparisonIterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base
{
	friend class iterator_core_access;

	typedef typename detail::delegate_comparison_base<_Iterator, _ComparisonIterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base __base;

	_ComparisonIterator _cmp_iterator;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;

	typedef _ComparisonIterator comparison_iterator;

public:
	delegate_comparison_iterator()
	: __base()
	, _cmp_iterator()
	{}

	explicit delegate_comparison_iterator(comparison_iterator __cmp_iterator)
	: __base()
	, _cmp_iterator(__cmp_iterator)
	{}

	delegate_comparison_iterator(iterator_type __x, comparison_iterator __cmp_iterator)
	: __base(__x)
	, _cmp_iterator(__cmp_iterator)
	{}

	delegate_comparison_iterator(const delegate_comparison_iterator& __x)
	: __base(__x)
	, _cmp_iterator(__x._cmp_iterator)
	{}

	using __base::operator=;

	const _ComparisonIterator& compare_with() const
	{ return _cmp_iterator; }

	_ComparisonIterator& compare_with()
	{ return _cmp_iterator; }

private:
	void increment()
	{
		++this->base_reference();
		++_cmp_iterator;
	}

	void decrement()
	{
		--this->base_reference();
		--_cmp_iterator;
	}

	void advance(difference_type n)
	{
		this->base_reference() += n;
		_cmp_iterator += n;
	}

	void recoil(difference_type n)
	{
		this->base_reference() -= n;
		_cmp_iterator -= n;
	}

	bool equal(const delegate_comparison_iterator& x) const
	{ return _cmp_iterator == x._cmp_iterator; }

	bool less(const delegate_comparison_iterator& x) const
	{ return _cmp_iterator < x._cmp_iterator; }
};

template <typename _Iterator, typename _ComparisonIterator>
delegate_comparison_iterator<_Iterator, _ComparisonIterator>
make_delegate_comparison_iterator(_Iterator x, _ComparisonIterator cmp_x)
{ return delegate_comparison_iterator<_Iterator, _ComparisonIterator>(x, cmp_x); }

template <typename _Iterator>
delegate_comparison_iterator<_Iterator, _Iterator>
make_delegate_comparison_iterator(_Iterator x)
{ return delegate_comparison_iterator<_Iterator, _Iterator>(x); }

}}

#endif