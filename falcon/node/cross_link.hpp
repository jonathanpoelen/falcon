#ifndef _FALCON_NODE_CROSS_LINK_HPP
#define _FALCON_NODE_CROSS_LINK_HPP

#include <utility> //std::swap
#include <falcon/c++/constexpr.hpp>
#include <falcon/arg/rotate_arg.hpp>

namespace falcon{ namespace node {

template<typename _Up, typename _Down = _Up, typename _Left = _Down, typename _Right = _Left>
struct cross_link
{
	typedef cross_link<_Up, _Down, _Left, _Right> self_type;
	typedef _Up up_type;
	typedef _Down down_type;
	typedef _Left left_type;
	typedef _Right right_type;

	left_type left;
	up_type up;
	right_type right;
	down_type down;

	cross_link(const left_type& __left, const up_type& __up, const right_type& __right, const down_type& __down)
	: left(__left)
	, up(__up)
	, right(__right)
	, down(__down)
	{}

	bool is_superposed(const self_type& other) const
	{ return is_superposed<_Up, _Down, _Left, _Right>(other); }

	template<typename __Up, typename __Down, typename __Left, typename __Right>
	bool is_superposed(const cross_link<_Up, _Down, _Left, _Right>& other) const
	{
		return other.up == up
			&& other.down == down
			&& other.left == left
			&& other.right == right;
	}

	bool is_rotate_superposed(const self_type& other) const
	{ return is_superposed<_Up, _Down, _Left, _Right>(other); }

	template<typename __Up, typename __Down, typename __Left, typename __Right>
	bool is_rotate_superposed(const cross_link<_Up, _Down, _Left, _Right>& other) const
	{
		switch (other.up) {
			case up:
				return other.down == down
					&& other.left == left
					&& other.right == right;
			case right:
				return other.right == down
					&& other.down == left
					&& other.left == up;
			case down:
				return other.right == left
					&& other.down == up
					&& other.left == right;
			case left:
				return other.right == up
					&& other.down == right
					&& other.left == down;
			default:
				return false;
		}
	}

	void set(const up_type& __up, const down_type& __down, const left_type& __left, const right_type& __right)
	{
		up = __up;
		down = __down;
		left = __left;
		right = __right;
	}

	void set(const self_type& other)
	{
		up = other.up;
		down = other.down;
		left = other.left;
		right = other.right;
	}

	void rotate90()
	{ falcon::rotate_arg<1>(up, right, down, left); }
	void rotate180()
	{ falcon::rotate_arg<2>(up, right, down, left); }
	void rotate270()
	{ falcon::rotate_arg<3>(up, right, down, left); }

	void rotate_horizontal()
	{ std::swap<>(up, down); }
	void rotate_vertical()
	{ std::swap<>(left, right); }

	void rotate_left_down()
	{
		std::swap<>(up, right);
		std::swap<>(left, down);
	}
	void rotate_down_right()
	{
		std::swap<>(up, left);
		std::swap<>(right, down);
	}

	void reverse()
	{
		rotate_horizontal();
		rotate_vertical();
	}
};

template<typename _Up, typename _Down, typename _Left, typename _Right>
bool operator==(const cross_link<_Up, _Down, _Left, _Right>& a, const cross_link<_Up, _Down, _Left, _Right>& b)
{ return a.is_superposed(b); }

template<typename _Up, typename _Down, typename _Left, typename _Right>
bool operator!=(const cross_link<_Up, _Down, _Left, _Right>& a, const cross_link<_Up, _Down, _Left, _Right>& b)
{ return !(a == b); }


template<typename _Up, typename _Down = _Up, typename _Left = _Down, typename _Right = _Left>
class restrict_cross_link
{
	typedef cross_link<_Up, _Down, _Left, _Right> link_type;
public:
	typedef restrict_cross_link<_Up, _Down, _Left, _Right> self_type;
	typedef typename link_type::up_type up_type;
	typedef typename link_type::down_type down_type;
	typedef typename link_type::left_type left_type;
	typedef typename link_type::right_type right_type;

protected:
	cross_link<_Up, _Down, _Left, _Right> _cross_link;

public:
	CPP_CONSTEXPR restrict_cross_link()
	: _cross_link()
	{}

	CPP_CONSTEXPR restrict_cross_link(const link_type& cross_link)
	: _cross_link(cross_link)
	{}

	CPP_CONSTEXPR restrict_cross_link(const up_type& __up, const down_type& __down, const left_type& __left, const right_type& __right)
	: _cross_link(__up, __down, __left, __right)
	{}

	CPP_CONSTEXPR restrict_cross_link(const self_type& other)
	: _cross_link(other._cross_link)
	{}

	self_type& operator=(const self_type& other)
	{
		_cross_link = other._cross_link;
		return *this;
	}

	self_type& operator=(const link_type& other)
	{
		_cross_link.set(other);
		return *this;
	}

	const up_type& up() const
	{ return _cross_link.up; }
	const down_type& down() const
	{ return _cross_link.down; }
	const left_type& left() const
	{ return _cross_link.left; }
	const right_type& right() const
	{ return _cross_link.right; }

	bool is_superposed(const self_type& other) const
	{ return _cross_link.is_superposed(other._cross_link); }

	bool is_superposed(const link_type& other) const
	{ return _cross_link.is_superposed(other); }

	template<typename __Up, typename __Down, typename __Left, typename __Right>
	bool is_superposed(const restrict_cross_link<_Up, _Down, _Left, _Right>& other) const
	{ return _cross_link.is_superposed(other._cross_link); }

	template<typename __Up, typename __Down, typename __Left, typename __Right>
	bool is_superposed(const cross_link<_Up, _Down, _Left, _Right>& other) const
	{ return _cross_link.is_superposed(other); }

	bool is_rotate_superposed(const self_type& other) const
	{ return _cross_link.is_superposed(other._cross_link); }

	bool is_rotate_superposed(const link_type& other) const
	{ return _cross_link.is_superposed(other); }

	template<typename __Up, typename __Down, typename __Left, typename __Right>
	bool is_rotate_superposed(const restrict_cross_link<_Up, _Down, _Left, _Right>& other) const
	{ return _cross_link.is_rotate_superposed(other._cross_link); }

	template<typename __Up, typename __Down, typename __Left, typename __Right>
	bool is_rotate_superposed(const cross_link<_Up, _Down, _Left, _Right>& other) const
	{ return _cross_link.is_rotate_superposed(other); }
};

template<typename _Up, typename _Down, typename _Left, typename _Right>
bool operator==(const restrict_cross_link<_Up, _Down, _Left, _Right>& a, const restrict_cross_link<_Up, _Down, _Left, _Right>& b)
{ return a.is_superposed(b); }

template<typename _Up, typename _Down, typename _Left, typename _Right>
bool operator!=(const restrict_cross_link<_Up, _Down, _Left, _Right>& a, const restrict_cross_link<_Up, _Down, _Left, _Right>& b)
{ return !(a == b); }

} }


#endif