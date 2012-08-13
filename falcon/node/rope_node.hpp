#ifndef _FALCON_NODE_ROPE_NODE_HPP
#define _FALCON_NODE_ROPE_NODE_HPP

#include <falcon/node/rope_link.hpp>
#include <falcon/node/detail/set_node.hpp>
#include <falcon/node/iterator.hpp>
#include <falcon/preprocessor/getter.hpp>

namespace falcon { namespace node {

template<typename _T>
struct rope_node
{
	typedef rope_node<_T> self_type;
	typedef self_type* adjacent_type;
	typedef const self_type* const_adjacent_type;
	typedef rope_link<adjacent_type> link_type;
	typedef _T value_type;

private:
	typedef left_node_access_traits<adjacent_type> left_access_traits;
	typedef right_node_access_traits<adjacent_type> right_access_traits;

public:
	typedef basic_node_iterator<double_node_access_traits<left_access_traits, right_access_traits> > left_iterator;
	typedef basic_node_iterator<double_node_access_traits<right_access_traits, left_access_traits> > right_iterator;

private:
	typedef detail::__set_node<self_type> __set_traits;

protected:
	value_type _value;
	link_type _link;

public:
	CPP_CONSTEXPR rope_node()
	: _value()
	, _link(0,0)
	{}

	rope_node(const value_type& value, adjacent_type __left = 0, adjacent_type __right = 0)
	: _value(value)
	, _link(__left, __right)
	{
		if (__left)
			__left->_link.right = this;
		if (__right)
			__right->_link.left = this;
	}

	rope_node(adjacent_type __left, adjacent_type __right = 0)
	: _value()
	, _link(__left, __right)
	{
		if (__left)
			__left->_link.right = this;
		if (__right)
			__right->_link.left = this;
	}

	CPP_CONSTEXPR rope_node(const value_type& value, const link_type& __link)
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

	void left(adjacent_type __left)
	{ __set_traits::set_left(this, __left); }

	adjacent_type left()
	{ return _link.left; }

	const_adjacent_type left() const
	{ return _link.left; }

	void right(adjacent_type __right)
	{ __set_traits::set_right(this, __right); }

	adjacent_type right()
	{ return _link.right; }

	const_adjacent_type right() const
	{ return _link.right; }

	void set(adjacent_type _left, adjacent_type _right)
	{
		left(_left);
		right(_right);
	}

	const link_type& link() const
	{ return _link; }

	link_type& _M_link()
	{ return _link; }

	void detach()
	{
		if (_link.right) {
			_link.right->left = 0;
			_link.right = 0;
		}
		if (_link.left) {
			_link.left->right = 0;
			_link.left = 0;
		}
	}
};

template<typename _T>
bool operator==(const rope_node<_T>& a, const rope_node<_T>& b)
{ return a.get() == b.get() && a.link().is_superposed(b.link()); }

template<typename _T>
bool operator!=(const rope_node<_T>& a, const rope_node<_T>& b)
{ return !(a == b); }

} }

#endif