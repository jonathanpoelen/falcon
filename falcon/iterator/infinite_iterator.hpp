#ifndef _FALCON_ITERATOR_INFINITE_ITERATOR_HPP
#define _FALCON_ITERATOR_INFINITE_ITERATOR_HPP

#include <falcon/infinite.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

namespace iterator {

template <typename _Iterator>
class infinite_iterator
: public infinite_base<_Iterator>
{
	typedef infinite_base<_Iterator> base_type;
	typedef infinite_iterator<_Iterator> self_type;

public:
	typedef typename base_type::value_type iterator;

private:
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::pointer pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

public:
	infinite_iterator(const iterator& begin, const iterator& end)
	: base_type(begin, end)
	{}

	infinite_iterator(const iterator& begin, const iterator& it, const iterator& end)
	: base_type(begin, it, end)
	{}

	template <typename _Container>
	infinite_iterator(_Container& container)
	: base_type(begin(container), end(container))
	{}

	template <typename _Container>
	infinite_iterator(_Container& container, const iterator& it)
	: base_type(begin(container), it, end(container))
	{}

	infinite_iterator(const self_type& other)
	: base_type(other)
	{}

	self_type& operator=(const iterator& it)
	{
		base_type::operator=(it);
		return *this;
	}

	FALCON_MEMBER_GETTER(reference, operator*, *base_type::_it)
	FALCON_MEMBER_GETTER(pointer, operator->, base_type::_it.operator->())

	using infinite_base<_Iterator>::next;
	using infinite_base<_Iterator>::prev;

	FALCON_MEMBER_INCREMENT(self_type, base_type::next())
	FALCON_MEMBER_DECREMENT(self_type, base_type::prev())

	bool operator==(const self_type&)
	{ return false; }
	bool operator!=(const self_type&)
	{ return true; }
};

template <typename _Container, typename _Iterator = typename _Container::iterator>
iterator::infinite_iterator<_Iterator> make_infinite_iterator(_Container& c) {
	return iterator::infinite_iterator<_Iterator>(c);
}

template <typename _Container, typename _Iterator = typename _Container::iterator>
iterator::infinite_iterator<_Iterator> make_infinite_iterator(_Container& c, const _Iterator& it) {
	return iterator::infinite_iterator<_Iterator>(c, it);
}

template <typename _Iterator>
iterator::infinite_iterator<_Iterator> make_infinite_iterator(const _Iterator& begin, const _Iterator& end) {
	return iterator::infinite_iterator<_Iterator>(begin, end);
}

template <typename _Iterator>
iterator::infinite_iterator<_Iterator> make_infinite_iterator(const _Iterator& begin, _Iterator it, const _Iterator& end) {
	return iterator::infinite_iterator<_Iterator>(begin, it, end);
}

}

}

#endif