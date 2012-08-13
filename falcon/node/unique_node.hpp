#ifndef _FALCON_NODE_UNIQUE_NODE_HPP
#define _FALCON_NODE_UNIQUE_NODE_HPP

#include <falcon/node/unique_link.hpp>
#include <falcon/node/iterator.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/preprocessor/iterator.hpp>

namespace falcon { namespace node {

template<typename _T>
struct unique_node
{
	typedef unique_node<_T> self_type;
	typedef self_type* adjacent_type;
	typedef const self_type* const_adjacent_type;
	typedef unique_link<adjacent_type> link_type;
	typedef _T value_type;
	typedef basic_node_iterator<next_node_access_traits<adjacent_type> > iterator;
	typedef basic_node_iterator<next_node_access_traits<const_adjacent_type> > const_iterator;

protected:
	value_type _value;
	link_type _link;

public:
	CPP_CONSTEXPR unique_node()
	: _value()
	, _link(0)
	{}

	unique_node(const value_type& value, adjacent_type __next = 0)
	: _value(value)
	, _link(__next)
	{}

	unique_node(adjacent_type __next = 0)
	: _value()
	, _link(__next)
	{}

	CPP_CONSTEXPR unique_node(const value_type& value, const link_type& __link)
	: _value(value)
	, _link(__link)
	{}

	self_type& operator=(const value_type& other)
	{
		_value = other;
		return *this;
	}

	FALCON_CAST_GETTER(value_type, _value)

	value_type& get()
	{ return _value; }
	const value_type& get() const
	{ return _value; }

	value_type& operator*()
	{ return _value; }
	const value_type& operator*() const
	{ return _value; }

	value_type* operator->()
	{ return &_value; }
	const value_type* operator->() const
	{ return &_value; }

	void next(adjacent_type __next)
	{ _link.next = __next; }

	adjacent_type next()
	{ return _link.next; }

	const_adjacent_type next() const
	{ return _link.next; }

	void set(adjacent_type _next)
	{ next(_next); }

	const link_type& link() const
	{ return _link; }

	FALCON_MEMBER_ITERATOR_ARGS((this), (0))
};

template<typename _T>
bool operator==(const unique_node<_T>& a, const unique_node<_T>& b)
{ return *a == *b && a.link()->is_superposed(b.link()); }

template<typename _T>
bool operator!=(const unique_node<_T>& a, const unique_node<_T>& b)
{ return !(a == b); }

} }

#endif