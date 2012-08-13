#ifndef _FALCON_NODE_ROPE_LINK_HPP
#define _FALCON_NODE_ROPE_LINK_HPP

#include <utility> //std::swap
#include <falcon/c++/constexpr.hpp>

namespace falcon{ namespace node {

template<typename _Left, typename _Right = _Left>
struct rope_link
{
	typedef rope_link<_Left, _Right> self_type;
	typedef _Left left_type;
	typedef _Right right_type;

	left_type left;
	right_type right;

	CPP_CONSTEXPR rope_link(const left_type& __left, const right_type& __right)
	: left(__left)
	, right(__right)
	{}

	CPP_CONSTEXPR rope_link(const left_type& __left)
	: left(__left)
	, right()
	{}

	bool is_superposed(const self_type& other) const
	{ return is_superposed<_Left, _Right>(other); }

	template<typename __Left, typename __Right>
	bool is_superposed(const rope_link<_Left, _Right>& other) const
	{
		return other.left == left
			&& other.right == right;
	}

	bool is_rotate_superposed(const self_type& other) const
	{ return is_superposed<_Left, _Right>(other); }

	template<typename __Left, typename __Right>
	bool is_rotate_superposed(const rope_link<_Left, _Right>& other) const
	{
		return (other.left == right && other.right == left)
			|| (other.left == left && other.right == right);
	}

	void set(const left_type& __left, const right_type& __right)
	{
		left = __left;
		right = __right;
	}

	void set(const self_type& other)
	{
		left = other.left;
		right = other.right;
	}

	void reverse()
	{ std::swap<>(left, right); }
};

template<typename _Left, typename _Right>
bool operator==(const rope_link<_Left, _Right>& a, const rope_link<_Left, _Right>& b)
{ return a.is_superposed(b); }

template<typename _Left, typename _Right>
bool operator!=(const rope_link<_Left, _Right>& a, const rope_link<_Left, _Right>& b)
{ return !(a == b); }


template<typename _Left, typename _Right = _Left>
class restrict_rope_link
{
	typedef rope_link<_Left, _Right> link_type;
public:
	typedef restrict_rope_link<_Left, _Right> self_type;
	typedef typename link_type::left_type left_type;
	typedef typename link_type::right_type right_type;

protected:
	rope_link<_Left, _Right> _rope_link;

public:
	CPP_CONSTEXPR restrict_rope_link()
	: _rope_link()
	{}

	CPP_CONSTEXPR restrict_rope_link(const link_type& rope_link)
	: _rope_link(rope_link)
	{}

	CPP_CONSTEXPR restrict_rope_link(const left_type& __left)
	: _rope_link(__left)
	{}

	CPP_CONSTEXPR restrict_rope_link(const left_type& __left, const right_type& __right)
	: _rope_link(__left, __right)
	{}

	CPP_CONSTEXPR restrict_rope_link(const self_type& other)
	: _rope_link(other._rope_link)
	{}

	self_type& operator=(const self_type& other)
	{
		_rope_link = other._rope_link;
		return *this;
	}

	self_type& operator=(const link_type& other)
	{
		_rope_link.set(other);
		return *this;
	}

	const left_type& left() const
	{ return _rope_link.left; }
	const right_type& right() const
	{ return _rope_link.right; }

	bool is_superposed(const self_type& other) const
	{ return _rope_link.is_superposed(other._rope_link); }

	bool is_superposed(const link_type& other) const
	{ return _rope_link.is_superposed(other); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_superposed(const restrict_rope_link<_Left, _Right>& other) const
	{ return _rope_link.is_superposed(other._rope_link); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_superposed(const rope_link<_Left, _Right>& other) const
	{ return _rope_link.is_superposed(other); }

	bool is_rotate_superposed(const self_type& other) const
	{ return _rope_link.is_superposed(other._rope_link); }

	bool is_rotate_superposed(const link_type& other) const
	{ return _rope_link.is_superposed(other); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_rotate_superposed(const restrict_rope_link<_Left, _Right>& other) const
	{ return _rope_link.is_rotate_superposed(other._rope_link); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_rotate_superposed(const rope_link<_Left, _Right>& other) const
	{ return _rope_link.is_rotate_superposed(other); }
};

template<typename _Left, typename _Right>
bool operator==(const restrict_rope_link<_Left, _Right>& a, const restrict_rope_link<_Left, _Right>& b)
{ return a.is_superposed(b); }

template<typename _Left, typename _Right>
bool operator!=(const restrict_rope_link<_Left, _Right>& a, const restrict_rope_link<_Left, _Right>& b)
{ return !(a == b); }

} }

#endif