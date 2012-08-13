#ifndef _FALCON_ITERATOR_POINTER_ITERATOR_ITERATOR_HPP
#define _FALCON_ITERATOR_POINTER_ITERATOR_ITERATOR_HPP

#include <falcon/c++0x/syntax.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>

namespace falcon {

namespace iterator {

template <typename _Iterator>
class pointer_iterator_iterator
{
	typedef pointer_iterator_iterator<_Iterator> self_type;

public:
	typedef _Iterator iterator;

private:
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef typename std::remove_reference<decltype(**std::declval<_Iterator>())>::type value_type;
	typedef typename iterator_traits::value_type pointer;
	typedef value_type& reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	iterator _it;

public:
	pointer_iterator_iterator(const iterator& it)
	: _it(it)
	{}

	pointer_iterator_iterator(const self_type& other)
	: _it(other._it)
	{}

	self_type& operator=(const value_type& value)
	{
		**_it = value;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		_it = it;
		return *this;
	}

	self_type& operator=(const self_type& other)
	{
		_it = other._it;
		return *this;
	}

	FALCON_MEMBER_GETTER(reference, operator*, **_it)
	FALCON_MEMBER_GETTER(pointer, operator->, *_it)

	FALCON_MEMBER_INCREMENT(self_type, ++_it)
	FALCON_MEMBER_DECREMENT(self_type, --_it)

	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(self_type, _it, other._it)

	const iterator& base() const
	{ return _it; }
	iterator& base()
	{ return _it; }
};


template <typename _Iterator>
typename pointer_iterator_iterator<_Iterator>::difference_type
operator-(const pointer_iterator_iterator<_Iterator>& a,
		  const pointer_iterator_iterator<_Iterator>& b)
{ return a.base() - b.base(); }

template <typename _Iterator>
pointer_iterator_iterator<_Iterator>
operator+(const pointer_iterator_iterator<_Iterator>& a, int n)
{ return a.base() + n; }

template <typename _Iterator>
pointer_iterator_iterator<_Iterator>
operator-(const pointer_iterator_iterator<_Iterator>& a, int n)
{ return a.base() - n; }

template <typename _Container, typename _Iterator = typename _Container::iterator>
iterator::pointer_iterator_iterator<_Iterator> make_pointer_iterator_iterator(_Container& c) {
	return iterator::pointer_iterator_iterator<_Iterator>(c);
}

template <typename _Container, typename _Iterator = typename _Container::iterator>
iterator::pointer_iterator_iterator<_Iterator> make_pointer_iterator_iterator(_Container& c, const _Iterator& it) {
	return iterator::pointer_iterator_iterator<_Iterator>(c, it);
}

template <typename _Iterator>
iterator::pointer_iterator_iterator<_Iterator> make_pointer_iterator_iterator(const _Iterator& begin, const _Iterator& end) {
	return iterator::pointer_iterator_iterator<_Iterator>(begin, end);
}

template <typename _Iterator>
iterator::pointer_iterator_iterator<_Iterator> make_pointer_iterator_iterator(const _Iterator& begin, _Iterator it, const _Iterator& end) {
	return iterator::pointer_iterator_iterator<_Iterator>(begin, it, end);
}

}

}

#endif