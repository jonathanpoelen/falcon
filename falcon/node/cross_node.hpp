#ifndef _FALCON_NODE_CROSS_NODE_HPP
#define _FALCON_NODE_CROSS_NODE_HPP

#include <falcon/arg/rotate_arg.hpp>
#include <falcon/node/cross_link.hpp>
#include <falcon/node/detail/set_node.hpp>
#include <falcon/node/iterator.hpp>
#include <falcon/preprocessor/getter.hpp>

namespace falcon { namespace node {

template<typename _T>
struct cross_node
{
	typedef cross_node<_T> self_type;
	typedef self_type* adjacent_type;
	typedef const self_type* const_adjacent_type;
	typedef cross_link<adjacent_type> link_type;
	typedef _T value_type;

private:
	typedef left_node_access_traits<adjacent_type> left_access_traits;
	typedef right_node_access_traits<adjacent_type> right_access_traits;
	typedef up_node_access_traits<adjacent_type> up_access_traits;
	typedef down_node_access_traits<adjacent_type> down_access_traits;

public:
	typedef basic_node_iterator<double_node_access_traits<left_access_traits, right_access_traits> > left_iterator;
	typedef basic_node_iterator<double_node_access_traits<right_access_traits, left_access_traits> > right_iterator;
	typedef basic_node_iterator<double_node_access_traits<up_access_traits, down_access_traits> > up_iterator;
	typedef basic_node_iterator<double_node_access_traits<down_access_traits, up_access_traits> > down_iterator;

private:
	typedef detail::__set_node<self_type> __set_traits;

protected:
	value_type _value;
	link_type _link;

public:
	CPP_CONSTEXPR cross_node()
	: _value()
	, _link(0,0,0,0)
	{}

private:
	void init()
	{
		if (_link.left)
			_link.left->_link.right = this;
		if (_link.up)
			_link.up->_link.down = this;
		if (_link.right)
			_link.right->_link.left = this;
		if (_link.down)
			_link.down->_link.up = this;
	}

public:
	cross_node(const value_type& value, adjacent_type __left = 0, adjacent_type __up = 0, adjacent_type __right = 0, adjacent_type __down = 0)
	: _value(value)
	, _link(__left, __up, __right, __down)
	{
		init();
	}

	cross_node(adjacent_type __left, adjacent_type __up = 0, adjacent_type __right = 0, adjacent_type __down = 0)
	: _value()
	, _link(__left, __up, __right, __down)
	{
		init();
	}

	CPP_CONSTEXPR cross_node(const value_type& value, const link_type& __link)
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

	void up(adjacent_type __up)
	{ __set_traits::set_up(this, __up); }

	adjacent_type up()
	{ return _link.up; }

	const_adjacent_type up() const
	{ return _link.up; }

	void left(adjacent_type __left)
	{ __set_traits::set_left(this, __left); }

	adjacent_type left()
	{ return _link.left; }

	const_adjacent_type left() const
	{ return _link.left; }

	void down(adjacent_type __down)
	{ __set_traits::set_down(this, __down); }

	adjacent_type down()
	{ return _link.down; }

	const_adjacent_type down() const
	{ return _link.down; }

	void right(adjacent_type __right)
	{ __set_traits::set_right(this, __right); }

	adjacent_type right()
	{ return _link.right; }

	const_adjacent_type right() const
	{ return _link.right; }

	void set(adjacent_type _up, adjacent_type _down, adjacent_type _left, adjacent_type _right)
	{
		up(_up);
		left(_left);
		down(_down);
		right(_right);
	}

	const link_type& link() const
	{ return _link; }

	link_type& _M_link()
	{ return _link; }

	void detach()
	{
		if (_link.up) {
			_link.up->down = 0;
			_link.up = 0;
		}
		if (_link.right) {
			_link.right->left = 0;
			_link.right = 0;
		}
		if (_link.down) {
			_link.down->up = 0;
			_link.down = 0;
		}
		if (_link.left) {
			_link.left->right = 0;
			_link.left = 0;
		}
	}
};

template<typename _T>
bool operator==(const cross_node<_T>& a, const cross_node<_T>& b)
{ return a.get() == b.get() && a.link().is_superposed(b.link()); }

template<typename _T>
bool operator!=(const cross_node<_T>& a, const cross_node<_T>& b)
{ return !(a == b); }

} }

#endif