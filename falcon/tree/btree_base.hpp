#ifndef _FALCON_TREE_BTREE_BASE_HPP
#define _FALCON_TREE_BTREE_BASE_HPP

#include <utility>
#include <stdexcept>
#include <falcon/c++/constexpr.hpp>
#include <falcon/preprocessor/getter.hpp>

namespace falcon {

template <typename _T, typename _Child, bool _ValueOnlyInLeaf = false>
struct btree_base
{
	typedef btree_base<_T, _Child, false> self_type;
	typedef _T value_type;
	typedef _Child* tree_type;
	typedef const _Child* const_tree_type;

protected:
	tree_type _left, _right;
	value_type _value;

public:
	CPP_CONSTEXPR btree_base(const value_type& value = value_type())
	: _left(0)
	, _right(0)
	, _value(value)
	{}

	CPP_CONSTEXPR btree_base(tree_type __left, tree_type __right, const value_type& value = value_type())
	: _left(__left)
	, _right(__right)
	, _value(value)
	{}

protected:
	self_type& operator=(const self_type& other)
	{
		_left = other._left;
		_right = other._right;
		_value = other._value;
		return *this;
	}

public:
	self_type& operator=(const value_type& value)
	{
		_value = value;
		return *this;
	}

	const_tree_type left() const
	{ return _left; }

	const_tree_type right() const
	{ return _right; }

	std::pair<const_tree_type, const_tree_type> children() const
	{ return std::make_pair(_left, _right); }

	void swap_value(self_type& other)
	{ std::swap(other._value, _value); }

	void swap_left(self_type& other)
	{ std::swap(_left, other._left); }

	void swap_right(self_type& other)
	{ std::swap(_right, other._right); }

	void swap_tree(self_type& other)
	{
		swap_left(other);
		swap_right(other);
	}

	void swap(self_type& other)
	{
		swap_value(other);
		swap_tree(other);
	}

	void left(tree_type __left)
	{ _left = __left; }

	void right(tree_type __right)
	{ _right = __right; }

	void children(tree_type __left, tree_type __right)
	{
		_left = __left;
		_right = __right;
	}

	void children(tree_type other)
	{ children(other->_left, other->_right); }
};

template <typename _T, typename _Child>
struct btree_base<_T, _Child, true>
{
	typedef btree_base<_T, _Child, true> self_type;
	typedef _T value_type;
	typedef value_type* pointer_type;
	typedef const value_type* const_pointer_type;
	typedef _Child* tree_type;

	static const bool in_left = true;
	static const bool in_right = false;

private:
	bool _is_leaf;
	union {
		struct {
			tree_type left;
			tree_type right;
		} children;
		pointer_type pointer;
	} _wrap;

public:
	btree_base(const value_type& value)
	: _is_leaf(true)
	{
		_wrap.pointer = new value_type(value);
	}

	btree_base(pointer_type pointer = 0)
	: _is_leaf(true)
	{
		_wrap.pointer = pointer;
	}

	btree_base(tree_type __left, tree_type __right)
	: _is_leaf(false)
	{
		_wrap.children.left = __left;
		_wrap.children.right = __right;
	}

	~btree_base()
	{
		if (_is_leaf)
			delete _wrap.pointer;
	}

protected:
	self_type& operator=(const self_type& other)
	{
		if (_is_leaf = other._is_leaf)
			_wrap.pointer = other._wrap.pointer;
		else
		{
			_wrap.children.left = other._wrap.children.left;
			_wrap.children.right = other._wrap.children.right;
		}
		return *this;
	}

public:
	self_type& operator=(pointer_type pointer)
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::operator=");
		delete _wrap.pointer;
		_wrap.pointer = pointer;
		return *this;
	}

	self_type& operator=(value_type value)
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::operator=");
		*_wrap.pointer = value;
		return *this;
	}

#if __cplusplus >= 201103L
	template<typename... _Args>
	void emplace(_Args&&... args)
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::operator=");
		new (_wrap.pointer) value_type(std::forward<_Args>(args)...);
	}
#else
	void emplace(...);
#endif

	bool is_leaf() const
	{ return _is_leaf; }

	tree_type left() const
	{
		if (_is_leaf)
			throw std::runtime_error("btree_base::left");
		return _wrap.children.left;
	}

	tree_type right() const
	{
		if (_is_leaf)
			throw std::runtime_error("btree_base::right");
		return _wrap.children.right;
	}

	std::pair<tree_type, tree_type> children() const
	{
		if (_is_leaf)
			throw std::runtime_error("btree_base::children");
		return std::make_pair(_wrap.children.left, _wrap.children.right);
	}

	pointer_type get()
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::get");
		return _wrap.pointer;
	}

	const_pointer_type get() const
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::get");
		return _wrap.pointer;
	}

	FALCON_MEMBER_GETTER(value_type, operator*, *get())

	void swap(pointer_type& pointer)
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::swap");
		std::swap(_wrap.pointer, pointer);
	}

	void swap(value_type& value)
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::swap");
		std::swap(*_wrap.pointer, value);
	}

	pointer_type detach_pointer()
	{
		if (!_is_leaf)
			throw std::runtime_error("btree_base::detach_pointer");
		pointer_type ret = _wrap.pointer;
		_wrap.pointer = 0;
		return ret;
	}

protected:
	void left(tree_type __left)
	{
		to_tree();
		_wrap.children.left = __left;
		_wrap.children.right = 0;
	}

	void right(tree_type __right)
	{
		to_tree();
		_wrap.children.left = 0;
		_wrap.children.right = __right;
	}

	void children(tree_type __left, tree_type __right)
	{
		to_tree();
		_wrap.children._left = __left;
		_wrap.children._right = __right;
	}

	void children(tree_type other)
	{ children(other->_left, other->_right); }

	bool extend_left(tree_type __left)
	{
		if (__left && _is_leaf)
		{
			*__left = _wrap.pointer;
			_is_leaf = false;
			_wrap.children.left = __left;
			_wrap.children.right = 0;
			return true;
		}
		return false;
	}

	bool extend_right(tree_type __right)
	{
		if (__right && _is_leaf)
		{
			*__right = _wrap.pointer;
			_is_leaf = false;
			_wrap.children.left = 0;
			_wrap.children.right = __right;
			return true;
		}
		return false;
	}

	bool extend_children(tree_type __left, tree_type __right, bool in_left = in_left)
	{
		if ((in_left ? __left : __right) && _is_leaf)
		{
			*(in_left ? __left : __right) = _wrap.pointer;
			_is_leaf = false;
			_wrap.children.left = __left;
			_wrap.children.right = __right;
			return true;
		}
		return false;
	}

	void swap_value(self_type& other)
	{
		if (_is_leaf || other._is_leaf)
			throw std::runtime_error("btree_base::swap_value");
		std::swap(_wrap.pointer, other._wrap.pointer);
	}

	void swap_left(self_type& other)
	{
		if (!_is_leaf || !other._is_leaf)
			throw std::runtime_error("btree_base::swap_left");
		std::swap(_wrap.children.left, other._wrap.children.left);
	}

	void swap_right(self_type& other)
	{
		if (!_is_leaf || !other._is_leaf)
			throw std::runtime_error("btree_base::swap_right");
		std::swap(_wrap.children.right, other._wrap.children.right);
	}

	void swap_children(self_type& other)
	{
		if (!_is_leaf || !other._is_leaf)
			throw std::runtime_error("btree_base::swap_children");
		std::swap(_wrap.children.left, other._wrap.children.left);
		std::swap(_wrap.children.right, other._wrap.children.right);
	}

	void swap(self_type& other)
	{
		if (_is_leaf)
			swap_value(other);
		else
			swap_children(other);
	}

private:
	void to_tree()
	{
		if (_is_leaf)
		{
			delete _wrap.pointer;
			_is_leaf = false;
		}
	}
};

}

#endif