#ifndef _FALCON_CONTAINER_GRID_CROSS_HPP
#define _FALCON_CONTAINER_GRID_CROSS_HPP

#include <algorithm>
#include <vector>
#include <falcon/c++/constexpr.hpp>
#include <falcon/coordinates/coord.hpp>
#include <falcon/coordinates/index.hpp>
#include <falcon/node/cross_node.hpp>
#include <falcon/node/iterator.hpp>
#include <falcon/preprocessor/iterator.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/container/detail/grid_cross_friend_algorithm.hpp>

namespace falcon {

namespace container {

template<typename _T>
class grid_cross
{
	typedef grid_cross<_T> self_type;
	typedef detail::grid_cross_friend_algorithm friend_algo;

public:
	typedef node::cross_node<_T> node_type;

private:
	typedef std::vector<node_type> container_type;

public:
	typedef node_type& reference_node;
	typedef const node_type& const_reference_node;
	typedef std::size_t size_type;

	typedef typename container_type::value_type value_type;
	typedef typename container_type::pointer pointer;
	typedef typename container_type::const_pointer const_pointer;
	typedef typename container_type::reference reference;
	typedef typename container_type::const_reference const_reference;

	typedef typename container_type::iterator iterator;
	typedef typename container_type::const_iterator const_iterator;
	typedef typename container_type::difference_type difference_type;
	typedef typename container_type::reverse_iterator reverse_iterator;
	typedef typename container_type::const_reverse_iterator const_reverse_iterator;

	typedef typename node_type::up_iterator up_iterator;
	typedef typename node_type::right_iterator right_iterator;
	typedef typename node_type::down_iterator down_iterator;
	typedef typename node_type::left_iterator left_iterator;

private:
	size_type _width;
	size_type _height;
	container_type _array;

public:
	grid_cross(size_type __width, size_type __height, const value_type value)
	: _width(__width)
	, _height(__height)
	, _array(__width * __height, value)
	{ friend_algo::init(*this); }

	grid_cross(size_type __width, size_type __height)
	: _width(__width)
	, _height(__height)
	, _array(__width * __height)
	{ friend_algo::init(*this); }

#if __cplusplus >= 201103L
	grid_cross(size_type __width, size_type __height, std::initializer_list<value_type> l)
	: _width(__width)
	, _height(__height)
	, _array(l)
	{
		if (l.size() != __width * __height){
			_array.resize(__width * __height);
		}
		friend_algo::init(*this);
	}

	grid_cross(self_type && other)
	: _width(other._width)
	, _height(other._height)
	, _array(std::forward<self_type>(other))
	{}
#endif

	size_type width() const
	{ return _width; }

	size_type height() const
	{ return _height; }

	size_type size() const
	{ return _array.size(); }

protected:
	void resize(char __flag, const value_type value = value_type())
	{
		_array.resize(size(), value);
		friend_algo::init(*this);

		if (__flag & 1)
			back_to_first_each_line();
		if (__flag & 2)
			back_to_first();

		if (__flag & 4)
			back_to_first_each_column();
		if (__flag & 8)
			back_to_first_column();

		if (__flag & 16)
			edge_connect_horizontal();
		if (__flag & 32)
			edge_connect_vertical();
	}

	char flag() const
	{
		char f = is_back_to_first_each_line() ? 1
			: is_back_to_first() ? 2
			: 0;

		if (is_back_to_first_each_column())
			f |= 4;
		if (is_back_to_first_column())
			f |= 8;

		if (is_edge_connect_horizontal())
			f |= 16;
		if (is_edge_connect_vertical())
			f |= 32;

		return f;
	}

public:
	void width(size_type __width, const value_type value = value_type())
	{
		char f = flag();
		_width = __width;
		resize(f, value);
	}

	void height(size_type __height, const value_type value = value_type())
	{
		char f = flag();
		_height = __height;
		resize(f, value);
	}

	void resize(size_type __width, size_type __height, const value_type value = value_type())
	{
		char f = flag();
		_width = __width;
		_height = __height;
		resize(f, value);
	}

	size_type max_size() const
	{ return _array.max_size(); }

	bool empty() const
	{ return _array.empty(); }

	void fill(const value_type& value)
	{ _array.fill(value); }

	void assign(const value_type& value)
	{ _array.assign(value); }

	void swap(self_type& other)
	{
        using std::swap;
		_array.swap(other._array);
		swap(_width, other._width);
		swap(_height, other._height);
	}

	FALCON_MEMBER_DELEGATE_ALL_ITERATOR(_array)

	reference operator[](size_type n)
	{ return _array[n]; }

	const_reference operator[](size_type n) const
	{ return _array[n]; }

	reference at(size_type n)
	{ return _array.at(n); }

	const_reference at(size_type n) const
	{ return _array.at(n); }

	bool in_grid(const node_type* node) const
	{ return std::find(_array.begin(), _array.end(), node) == _array.end(); }

	size_type index(const node_type* node) const
	{ return std::find(_array.begin(), _array.end(), node) - _array.begin(); }

	size_type index(size_type x, size_type y) const
	{ return coordinates::index(width(),x,y); }

	size_type coord_x(size_type __index) const
	{ return coordinates::coord_x(width(), __index); }

	size_type coord_y(size_type __index) const
	{ return coordinates::coord_y(width(), __index); }

	template<typename _Result = std::pair<size_type, size_type> >
	_Result coord(size_type __index) const
	{ return _Result(coord_x(__index), coord_y(__index)); }

	reference at(size_type x, size_type y)
	{ return at(index(x,y)); }

	const_reference at(size_type x, size_type y) const
	{ return at(index(x,y)); }

	reference operator()(size_type x, size_type y)
	{ return _array[index(x,y)]; }

	const_reference operator()(size_type x, size_type y) const
	{ return _array[index(x,y)]; }

	reference front()
	{ return _array.front(); }

	const_reference front() const
	{ return _array.front(); }

	reference back()
	{ return _array.back(); }

	const_reference back() const
	{ return _array.back(); }

	bool is_back_to_first() const
	{ return friend_algo::is_back_to_first(*this); }

	void back_to_first(bool connect = true)
	{ friend_algo::back_to_first(*this, connect); }

	bool is_back_to_first_each_line() const
	{ return friend_algo::is_back_to_first_each_line(*this); }

	void back_to_first_each_line(bool connect = true)
	{ friend_algo::back_to_first_each_line(*this, connect); }

	bool is_back_to_first_column() const
	{ return friend_algo::is_back_to_first_column(*this); }

	void back_to_first_column(bool connect = true)
	{ friend_algo::back_to_first_column(*this, connect); }

	bool is_back_to_first_each_column() const
	{ return friend_algo::is_back_to_first_each_column(*this); }

	void back_to_first_each_column(bool connect = true)
	{ friend_algo::back_to_first_each_column(*this, connect); }

	bool is_edge_connect_horizontal() const
	{ return friend_algo::is_edge_connect_horizontal(*this); }

	void edge_connect_horizontal(bool connect = true)
	{ friend_algo::edge_connect_horizontal(*this, connect); }

	bool is_edge_connect_vertical() const
	{ return friend_algo::is_edge_connect_vertical(*this); }

	void edge_connect_vertical(bool connect = true)
	{ friend_algo::edge_connect_vertical(*this, connect); }

	void edge_connect(bool connect = true)
	{ friend_algo::edge_connect(*this, connect); }

	bool is_edge_up(size_type __index) const
	{ return friend_algo::is_edge_up(*this, __index); }

	bool is_edge_down(size_type __index) const
	{ return friend_algo::is_edge_down(*this, __index); }

	bool is_edge_horizontal(size_type __index) const
	{ return friend_algo::is_edge_connect_horizontal(*this, __index); }

	bool is_edge_left(size_type __index) const
	{ return friend_algo::is_edge_left(*this, __index); }

	bool is_edge_right(size_type __index) const
	{ return friend_algo::is_edge_right(*this, __index); }

	bool is_edge_vertical(size_type __index) const
	{ return friend_algo::is_edge_vertical(*this, __index); }

	bool is_edge(size_type __index) const
	{ return friend_algo::is_edge(*this, __index); }
};

template<typename _Tp>
inline void swap(grid_cross<_Tp>& __one, grid_cross<_Tp>& __two)
{ __one.swap(__two); }

}

}

#endif
