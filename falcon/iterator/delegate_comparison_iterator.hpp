#ifndef _FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP
#define _FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP

#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>

namespace falcon {

namespace iterator {

template <typename _Iterator, typename _ComparisonIterator>
class delegate_comparison_iterator
{
	typedef delegate_comparison_iterator<_Iterator, _ComparisonIterator> self_type;
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _ComparisonIterator comparison_iterator;
	typedef _Iterator iterator;
	typedef typename iterator_traits::value_type value_type;
	//typedef typename iterator_traits::pointer pointer;
	typedef iterator pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	iterator _it;
	comparison_iterator _comparison;

public:
	delegate_comparison_iterator(const comparison_iterator& __comparison)
	: _it()
	, _comparison(__comparison)
	{}

	delegate_comparison_iterator(const iterator& it, const comparison_iterator& __comparison)
	: _it(it)
	, _comparison(__comparison)
	{}

	delegate_comparison_iterator(const self_type& other)
	: _it(other._it)
	, _comparison(other._comparison)
	{}

	self_type& operator=(const self_type& oher)
	{
		_it = oher._it;
		_comparison = oher._comparison;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		_it = it;
		return *this;
	}

	comparison_iterator& comparison()
	{ return _comparison; }
	const comparison_iterator& comparison() const
	{ return _comparison; }

	FALCON_MEMBER_GETTER(iterator, inner_iterator, _it)
	FALCON_MEMBER_GETTER(comparison_iterator, inner_comparison_iterator, _comparison)

	FALCON_MEMBER_GETTER(reference, operator*, *_it)
	FALCON_MEMBER_GETTER(pointer, operator->, *_it)

	FALCON_MEMBER_INCREMENT(self_type, ++_it; ++_comparison)
	FALCON_MEMBER_DECREMENT(self_type, --_it; --_comparison)

	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(self_type, _comparison, other._comparison)
};

template <typename _Iterator, typename _ComparisonIterator>
iterator::delegate_comparison_iterator<_Iterator, _ComparisonIterator> make_delegate_comparison_iterator(const _Iterator& begin, const _ComparisonIterator& comparison) {
	return iterator::delegate_comparison_iterator<_Iterator, _ComparisonIterator>(begin, comparison);
}

}

}

#endif