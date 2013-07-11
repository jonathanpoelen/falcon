#ifndef _FALCON_TREE_BTREE_HPP
#define _FALCON_TREE_BTREE_HPP

#include <utility>
#include <stdexcept>
#include <falcon/tree/btree_base.hpp>

namespace falcon {

namespace detail {
	template<typename _T>
	struct btree
	{
		typedef btree<_T> self_type;

		static _T* attach_parent(_T* _this, _T* other)
		{
			if (!other)
				return 0;
			_T* old = other->_parent;
			self_type::move_parent(old, _this);
			return old;
		}

		static void move_parent(_T* parent_old, _T* parent_new)
		{
			_T* parent = parent_old;
			if (parent && (parent = parent->_parent))
			{
				if (parent->left() == parent_new)
					parent->_M_base().left(parent_old);
				else if (parent->right() == parent_new)
					parent->_M_base().right(parent_old);
			}
		}

		static void swap_parent(_T*& _parent, _T& other)
		{
			self_type::move_parent(other._parent, _parent);
			self_type::move_parent(_parent, other._parent);
            using std::swap;
            swap(_parent, other._parent);
		}

		static void swap_left(_T* _this, _T& other)
        {
            using std::swap;
			_T* p1 = other.left();
			_T* p2 = _this->left();
			if (p1 && p2)
                swap(p1->_parent, p2->_parent);
			else if (p1)
				p1->_parent = 0;
			else if (p2)
				p2->_parent = 0;
			_this->_M_base().swap_left(other);
		}

		static void swap_right(_T* _this, _T& other)
        {
            using std::swap;
			_T* p1 = other.right();
			_T* p2 = _this->right();
			if (p1 && p2)
				swap(p1->_parent, p2->_parent);
			else if (p1)
				p1->_parent = 0;
			else if (p2)
				p2->_parent = 0;
			_this->_M_base().swap_right(other);
		}

		static void swap_tree(_T* _this, _T& other)
		{
			self_type::swap_left(_this, other);
			self_type::swap_right(_this, other);
			self_type::swap_parent(_this->_parent, other);
		}
	};
}

template<typename _T, bool _ValueOnlyInLeaf = false>
struct btree : protected btree_base<_T, btree<_T, false>, false>
{
	typedef btree< _T, _ValueOnlyInLeaf> self_type;

private:
	typedef btree_base<_T, btree<_T, false>, false> base_type;
	typedef ::falcon::detail::btree<self_type> detail_type;
	friend class ::falcon::detail::btree<self_type>;

public:
	typedef typename base_type::value_type value_type;

private:
	self_type* _parent;

public:
	CPP_CONSTEXPR btree()
	: base_type()
	, _parent(0)
	{}

	CPP_CONSTEXPR btree(self_type* parent)
	: base_type()
	, _parent(parent)
	{}

	CPP_CONSTEXPR btree(self_type* __left, self_type* __right, const value_type& value = value_type(), self_type* parent = 0)
	: base_type(__left, __right, value)
	, _parent(parent)
	{}

	CPP_CONSTEXPR btree(const value_type& value, self_type* parent = 0)
	: base_type(0, 0, value)
	, _parent(parent)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::operator=(other);
		_parent = other._parent;
		return *this;
	}

	self_type* left(self_type* other)
	{
		base_type::left(other);
		return detail_type::attach_parent(this, other);
	}

	self_type* right(self_type* other)
	{
		base_type::right(other);
		return detail_type::attach_parent(this, other);
	}

	FALCON_MEMBER_GETTER(value_type, get, base_type::_value)
	FALCON_MEMBER_GETTER(value_type, operator*, base_type::_value)

	self_type* right()
	{ return this->_right; }

	self_type* left()
	{ return this->_left; }

	const self_type* right() const
	{ return this->_right; }

	const self_type* left() const
	{ return this->_left; }

	self_type* sibling() const
	{
		if (_parent)
		{
			self_type* p = _parent->left();
			return p == this ? _parent->right() : p;
		}
		return 0;
	}

	std::pair<self_type*, self_type*> children(self_type* _left, self_type* _right)
	{ return std::make_pair(left(_left), right(_right)); }

	std::pair<self_type*, self_type*> children(self_type& other)
	{ return children(other.left, other.right); }

	void swap_parent(self_type& other)
	{ detail_type::swap_parent(_parent, other._parent); }

	void swap_left(self_type& other)
	{ detail_type::swap_left(this, other); }

	void swap_right(self_type& other)
	{ detail_type::swap_right(this, other); }

	void swap_tree(self_type& other)
	{ detail_type::swap_tree(this, other); }

	void swap(self_type& other)
	{
		base_type::swap_value(other);
		swap_tree(other);
	}

	base_type& _M_base()
	{ return *this; }

	const base_type& _M_base() const
	{ return *this; }
};

template<typename _T>
struct btree<_T, true>
: protected btree_base<_T, btree<_T, true>, true>
{
	typedef btree< _T, true> self_type;
	typedef _T value_type;

private:
	typedef btree_base<_T, btree<_T, true>, true> base_type;
	typedef ::falcon::detail::btree<self_type> detail_type;
	friend class ::falcon::detail::btree<self_type>;

private:
	self_type* _parent;

public:
	btree()
	: base_type()
	, _parent(0)
	{}

	btree(self_type* parent)
	: base_type()
	, _parent(parent)
	{}

	btree(self_type* __left, self_type* __right, const value_type& value = value_type(), self_type* parent = 0)
	: base_type(__left, __right, value)
	, _parent(parent)
	{}

	CPP_CONSTEXPR btree(const value_type& value, self_type* parent = 0)
	: base_type(0, 0, value)
	, _parent(parent)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::operator=(other);
		_parent = other._parent;
		return *this;
	}

	FALCON_MEMBER_GETTER(value_type, get, base_type::_value)
	FALCON_MEMBER_GETTER(value_type, operator*, base_type::_value)

	self_type* left(self_type* other)
	{
		base_type::left(other);
		return detail_type::attach_parent(this, other);
	}

	self_type* right(self_type* other)
	{
		base_type::right(other);
		return detail_type::attach_parent(this, other);
	}

	self_type* right()
	{ return this->_right; }

	self_type* left()
	{ return this->_left; }

	const self_type* right() const
	{ return this->_right; }

	const self_type* left() const
	{ return this->_left; }

	self_type* sibling() const
	{
		if (_parent)
		{
			self_type* p = _parent->left();
			return p == this ? _parent->right() : p;
		}
		return 0;
	}

	std::pair<self_type*, self_type*> children(self_type* _left, self_type* _right)
	{ return std::make_pair(left(_left), right(_right)); }

	std::pair<self_type*, self_type*> children(self_type& other)
	{ return children(other.left, other.right); }

	void swap_parent(self_type& other)
	{
		if (base_type::is_leaf() != other.is_leaf())
			throw std::runtime_error("btree::swap_parent");
		detail_type::swap_parent(_parent, other._parent);
	}

	void swap_left(self_type& other)
	{ detail_type::swap_left(this, other); }

	void swap_right(self_type& other)
	{ detail_type::swap_right(this, other); }

	void swap_tree(self_type& other)
	{ detail_type::swap_tree(this, other); }

	void swap(self_type& other)
	{
		swap_tree(other);
		base_type::swap_value(other);
	}

	std::pair<bool, self_type*> extend_left(self_type* __left)
	{
		if (base_type::extend_left(__left))
			return std::make_pair(true, detail_type::attach_parent(this, __left));
		return std::pair<bool, self_type*>(false , 0);
	}

	std::pair<bool, self_type*> extend_right(self_type* __right)
	{
		if (base_type::extend_right(__right))
			return std::make_pair(true, detail_type::attach_parent(this, __right));
		return std::pair<bool, self_type*>(false , 0);
	}

	std::pair<bool, std::pair<self_type*, self_type*> > extend_children(self_type* __left, self_type* __right, bool in_left = base_type::in_left)
	{
		if (base_type::extend_children(__right))
			return std::make_pair(true, std::make_pair(detail_type::attach_parent(this, __left), detail_type::attach_parent(this, __right)));
		return std::make_pair(false, std::pair<self_type*, self_type*>(0, 0));
	}

	base_type& _M_base()
	{ return *this; }

	const base_type& _M_base() const
	{ return *this; }
};

}

#endif
