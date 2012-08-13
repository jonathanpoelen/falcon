#ifndef _FALCON_TREE_FORWARD_BTREE_HPP
#define _FALCON_TREE_FORWARD_BTREE_HPP

#include <falcon/tree/btree_base.hpp>

namespace falcon {

template <typename _T, bool _ValueOnlyInLeaf = false>
struct forward_btree : public btree_base<_T, forward_btree<_T, false>, false>
{
	typedef forward_btree<_T, false> self_type;
	typedef _T value_type;

private:
	typedef btree_base<_T, forward_btree<_T, false>, false> base_type;

public:
	using base_type::left;
	using base_type::right;
	using base_type::children;
	using base_type::swap_left;
	using base_type::swap_right;
	using base_type::swap_tree;
	using base_type::swap;

public:
	CPP_CONSTEXPR forward_btree(const value_type& value = value_type())
	: base_type(value)
	{}

	CPP_CONSTEXPR forward_btree(self_type* __left, self_type* __right, const value_type& value = value_type())
	: base_type(__left, __right, value)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::operator=(other);
		return *this;
	}

	/*self_type& operator=(const value_type& value)
	{
		_value = value;
		return *this;
	}*/
};

template <typename _T>
struct forward_btree<_T, true> : btree_base<_T, forward_btree<_T, true>, true>
{
	typedef forward_btree<_T, true> self_type;
	typedef _T value_type;
	typedef _T* pointer_type;
	typedef const _T* const_pointer_type;

private:
	typedef btree_base<_T, forward_btree<_T, true>, true> base_type;

public:

public:
	using base_type::left;
	using base_type::right;
	using base_type::children;
	using base_type::extend_left;
	using base_type::extend_right;
	using base_type::extend_children;
	using base_type::swap_left;
	using base_type::swap_right;
	using base_type::swap_tree;
	using base_type::swap;

public:
	forward_btree(const value_type& value)
	: base_type(value)
	{}

	forward_btree(pointer_type pointer = 0)
	: base_type(pointer)
	{}

	forward_btree(self_type* __left, self_type* __right)
	: base_type(__left, __right)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::operator=(other);
		return *this;
	}
};

}

#endif