#ifndef _FALCON_ITERATOR_INFINITE_ITERATOR_HPP
#define _FALCON_ITERATOR_INFINITE_ITERATOR_HPP

#include <falcon/infinite.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator>
struct infinite_iterator
: infinite_base<_Iterator>
{
	typedef _Iterator iterator_type;

private:
	typedef infinite_base<_Iterator> base_type;
	typedef infinite_iterator<_Iterator> self_type;
	typedef std::iterator_traits<_Iterator> iterator_traits;

public:
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::pointer pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

public:
	infinite_iterator(iterator_type begin, iterator_type end)
	: base_type(begin, end)
	{}

	infinite_iterator(iterator_type begin, iterator_type it, iterator_type end)
	: base_type(begin, it, end)
	{}

	template <typename _Container>
	explicit infinite_iterator(_Container& container)
	: base_type(falcon::begin(container), falcon::end(container))
	{}

	infinite_iterator& operator=(const infinite_iterator& other)
	{
		base_type::_current = other._current;
		return *this;
	}

	infinite_iterator& operator=(const iterator_type& other)
	{
		base_type::_current = other;
		return *this;
	}

	template <typename _Container>
	infinite_iterator(_Container& container, iterator_type it)
	: base_type(falcon::begin(container), it, falcon::end(container))
	{}

	infinite_iterator(const self_type& other)
	: base_type(other)
	{}

	reference operator*() const
	{ return *base_type::_current; }

	reference operator*()
	{ return *base_type::_current; }

	pointer operator->() const
	{ return base_type::_current.operator->(); }

	pointer operator->()
	{ return base_type::_current.operator->(); }

	FALCON_MEMBER_INCREMENT(self_type, base_type::next())
	FALCON_MEMBER_DECREMENT(self_type, base_type::prev())

	bool operator==(const self_type&)
	{ return false; }
	bool operator!=(const self_type&)
	{ return true; }

	iterator_type base() const
	{ return base_type::_current; }
};

template <typename _Iterator>
bool operator==(const infinite_iterator<_Iterator>&,
				const infinite_iterator<_Iterator>&)
{ return false; }

template <typename _Iterator>
bool operator!=(const infinite_iterator<_Iterator>&,
				const infinite_iterator<_Iterator>&)
{ return true; }

template <typename _Iterator>
bool operator<(const infinite_iterator<_Iterator>&,
			   const infinite_iterator<_Iterator>&)
{ return false; }


template <typename _Container, typename _Iterator = typename range_access_iterator<_Container>::type>
infinite_iterator<_Iterator> make_infinite_iterator(_Container& c)
{ return infinite_iterator<_Iterator>(c); }

template <typename _Container, typename _Iterator = typename range_access_iterator<_Container>::type>
infinite_iterator<_Iterator> make_infinite_iterator(_Container& c, _Iterator it)
{ return infinite_iterator<_Iterator>(c, it); }

template <typename _Iterator>
infinite_iterator<_Iterator> make_infinite_iterator(_Iterator begin, _Iterator end)
{ return infinite_iterator<_Iterator>(begin, end); }

template <typename _Iterator>
infinite_iterator<_Iterator> make_infinite_iterator(_Iterator begin, _Iterator it, _Iterator end)
{ return infinite_iterator<_Iterator>(begin, it, end); }

}}

#endif