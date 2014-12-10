#ifndef _FALCON_NODE_TRI_LINK_HPP
#define _FALCON_NODE_TRI_LINK_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/functional/rotate_arg.hpp>

namespace falcon{ namespace node {

template<typename _Left, typename _Up = _Left, typename _Right = _Up>
struct tri_link
{
	typedef tri_link<_Left, _Up, _Right> self_type;
	typedef _Left left_type;
	typedef _Up up_type;
	typedef _Right right_type;

	left_type left;
	up_type up;
	right_type right;

	CPP_CONSTEXPR tri_link(const left_type& __left, const up_type& __up, const right_type& __right)
	: left(__left)
	, up(__up)
	, right(__right)
	{}

	CPP_CONSTEXPR tri_link(const left_type& __left, const right_type& __right)
	: left(__left)
	, up()
	, right(__right)
	{}

	bool is_superposed(const self_type& other) const
	{ return is_superposed<_Left, _Up, _Right>(other); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_superposed(const tri_link<_Left, _Up, _Right>& other) const
	{
		return other.up == up
			&& other.left == left
			&& other.right == right;
	}

	bool is_rotate_superposed(const self_type& other) const
	{ return is_superposed<_Left, _Up, _Right>(other); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_rotate_superposed(const tri_link<_Left, _Up, _Right>& other) const
	{
		switch (other.up) {
			case up:
				return other.left == left
					&& other.right == right;
			case right:
				return other.right == left
					&& other.left == up;
			case left:
				return other.right == up
					&& other.left == right;
			default:
				return false;
		}
	}

	void set(const left_type& __left, const up_type& __up, const right_type& __right)
	{
		left = __left;
		up = __up;
		right = __right;
	}

	void set(const self_type& other)
	{
		left = other.left;
		up = other.up;
		right = other.right;
	}

	void rotate120()
	{ falcon::rotate_arg<1>(up, right, left); }
	void rotate240()
	{ falcon::rotate_arg<2>(up, right, left); }

	void rotate_vertical()
    {
      using std::swap;
      swap(left, right);
    }
};

template<typename _Up, typename _Left, typename _Right>
bool operator==(const tri_link<_Left, _Up, _Right>& a, const tri_link<_Left, _Up, _Right>& b)
{ return a.is_superposed(b); }

template<typename _Up, typename _Left, typename _Right>
bool operator!=(const tri_link<_Left, _Up, _Right>& a, const tri_link<_Left, _Up, _Right>& b)
{ return !(a == b); }


template<typename _Left, typename _Up = _Left, typename _Right = _Up>
class restrict_tri_link
{
	typedef tri_link<_Left, _Up, _Right> link_type;
public:
	typedef restrict_tri_link<_Left, _Up, _Right> self_type;
	typedef typename link_type::up_type up_type;
	typedef typename link_type::left_type left_type;
	typedef typename link_type::right_type right_type;

protected:
	tri_link<_Left, _Up, _Right> _tri_link;

public:
	CPP_CONSTEXPR restrict_tri_link()
	: _tri_link()
	{}

	CPP_CONSTEXPR restrict_tri_link(const link_type& tri_link)
	: _tri_link(tri_link)
	{}

	CPP_CONSTEXPR restrict_tri_link(const left_type& __left, const up_type& __up, const right_type& __right)
	: _tri_link(__left, __up, __right)
	{}

	CPP_CONSTEXPR restrict_tri_link(const left_type& __left, const right_type& __right)
	: _tri_link(__left, __right)
	{}

	CPP_CONSTEXPR restrict_tri_link(const self_type& other)
	: _tri_link(other._tri_link)
	{}

	self_type& operator=(const self_type& other)
	{
		_tri_link = other._tri_link;
		return *this;
	}

	self_type& operator=(const link_type& other)
	{
		_tri_link.set(other);
		return *this;
	}

	const up_type& up() const
	{ return _tri_link.up; }
	const left_type& left() const
	{ return _tri_link.left; }
	const right_type& right() const
	{ return _tri_link.right; }

	bool is_superposed(const self_type& other) const
	{ return _tri_link.is_superposed(other._tri_link); }

	bool is_superposed(const link_type& other) const
	{ return _tri_link.is_superposed(other); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_superposed(const restrict_tri_link<_Left, _Up, _Right>& other) const
	{ return _tri_link.is_superposed(other._tri_link); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_superposed(const tri_link<_Left, _Up, _Right>& other) const
	{ return _tri_link.is_superposed(other); }

	bool is_rotate_superposed(const self_type& other) const
	{ return _tri_link.is_superposed(other._tri_link); }

	bool is_rotate_superposed(const link_type& other) const
	{ return _tri_link.is_superposed(other); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_rotate_superposed(const restrict_tri_link<_Left, _Up, _Right>& other) const
	{ return _tri_link.is_rotate_superposed(other._tri_link); }

	template<typename __Up, typename __Left, typename __Right>
	bool is_rotate_superposed(const tri_link<_Left, _Up, _Right>& other) const
	{ return _tri_link.is_rotate_superposed(other); }
};

template<typename _Up, typename _Left, typename _Right>
bool operator==(const restrict_tri_link<_Left, _Up, _Right>& a, const restrict_tri_link<_Left, _Up, _Right>& b)
{ return a.is_superposed(b); }

template<typename _Up, typename _Left, typename _Right>
bool operator!=(const restrict_tri_link<_Left, _Up, _Right>& a, const restrict_tri_link<_Left, _Up, _Right>& b)
{ return !(a == b); }

} }

#endif
