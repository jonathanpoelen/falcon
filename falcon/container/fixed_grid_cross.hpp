#ifndef _FALCON_CONTAINER_FIXED_GRID_CROSS_HPP
#define _FALCON_CONTAINER_FIXED_GRID_CROSS_HPP

#if __cplusplus >= 201103L
# include <forward_list>
#endif
#include <algorithm>
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

template<typename _T, std::size_t _Width, std::size_t _Height>
class fixed_grid_cross
{
	typedef fixed_grid_cross<_T, _Width, _Height> self_type;
	typedef detail::grid_cross_friend_algorithm friend_algo;

public:
	typedef node::cross_node<_T> node_type;

public:
	typedef node_type value_type;

	typedef node_type& reference_node;
	typedef const node_type& const_reference_node;
	typedef std::size_t size_type;

	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef node_type* iterator;
	typedef const node_type* const_iterator;
	typedef std::ptrdiff_t difference_type;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename node_type::up_iterator up_iterator;
	typedef typename node_type::right_iterator right_iterator;
	typedef typename node_type::down_iterator down_iterator;
	typedef typename node_type::left_iterator left_iterator;

private:
	node_type _array[_Width * _Height ? _Width * _Height : 1];

public:
	fixed_grid_cross()
	: _array()
	{
		friend_algo::init(*this);
	}

	fixed_grid_cross(const value_type value)
	{
		fill(value);
		friend_algo::init(*this);
	}

#if __cplusplus >= 201103L
	fixed_grid_cross(std::initializer_list<value_type> l)
	: _array{l}
	{ friend_algo::init(*this); }
#endif

	CPP_CONSTEXPR size_type width() const
	{ return _Width; }

	CPP_CONSTEXPR size_type height() const
	{ return _Height; }

	CPP_CONSTEXPR size_type size() const
	{ return _Width * _Height; }

	CPP_CONSTEXPR size_type max_size() const
	{ return _Width * _Height; }

	CPP_CONSTEXPR bool empty() const
	{ return size() == 0; }

	void fill(const value_type& value)
	{ std::fill_n(begin(), size(), value); }

	void assign(const value_type& value)
	{ fill(value); }

	void swap(self_type& __other)
	{ std::swap_ranges(begin(), end(), __other.begin()); }

	FALCON_MEMBER_ALL_ITERATOR(&_array[0], &_array[size()])

	reference operator[](size_type n)
	{ return _array[n]; }

	const_reference operator[](size_type n) const
	{ return _array[n]; }

	reference at(size_type n)
	{
		if (n >= size())
			std::__throw_out_of_range(__N("fixed_grid_cross::at"));
		return _array[n];
	}

	const_reference at(size_type n) const
	{
		if (n >= size())
			std::__throw_out_of_range(__N("fixed_grid_cross::at"));
		return _array[n];
	}

	bool in_grid(const node_type* node) const
	{ return data() <= node && node < data() + size(); }

	size_type index(const node_type* node) const
	{ return node - data(); }

	size_type index(size_type x, size_type y) const
	{ return coordinates::index(width(),x,y); }

	size_type coord_x(size_type __index) const
	{ return coordinates::coord_x<>(width(), __index); }

	size_type coord_y(size_type __index) const
	{ return coordinates::coord_y<>(width(), __index); }

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
	{ return *begin(); }

	const_reference front() const
	{ return *begin(); }

	reference back()
	{ return *(size() ? end() - 1 : end()); }

	const_reference back() const
	{ return *(size() ? end() - 1 : end()); }

	bool is_back_to_first() const
	{ return friend_algo::is_back_to_first<>(*this); }

	void back_to_first(bool connect = true)
	{ friend_algo::back_to_first<>(*this, connect); }

	bool is_back_to_first_each_line() const
	{ return friend_algo::is_back_to_first_each_line<>(*this); }

	void back_to_first_each_line(bool connect = true)
	{ friend_algo::back_to_first_each_line<>(*this, connect); }

	bool is_back_to_first_column() const
	{ return friend_algo::is_back_to_first_column<>(*this); }

	void back_to_first_column(bool connect = true)
	{ friend_algo::back_to_first_column<>(*this, connect); }

	bool is_back_to_first_each_column() const
	{ return friend_algo::is_back_to_first_each_column<>(*this); }

	void back_to_first_each_column(bool connect = true)
	{ friend_algo::back_to_first_each_column<>(*this, connect); }

	bool is_edge_connect_horizontal() const
	{ return friend_algo::is_edge_connect_horizontal<>(*this); }

	void edge_connect_horizontal(bool connect = true)
	{ friend_algo::edge_connect_horizontal<>(*this, connect); }

	bool is_edge_connect_vertical() const
	{ return friend_algo::is_edge_connect_vertical<>(*this); }

	void edge_connect_vertical(bool connect = true)
	{ friend_algo::edge_connect_vertical<>(*this, connect); }

	void edge_connect(bool connect = true)
	{ friend_algo::edge_connect<>(*this, connect); }

	bool is_edge_up(size_type __index) const
	{ return friend_algo::is_edge_up<>(*this, __index); }

	bool is_edge_down(size_type __index) const
	{ return friend_algo::is_edge_down<>(*this, __index); }

	bool is_edge_horizontal(size_type __index) const
	{ return friend_algo::is_edge_connect_horizontal<>(*this, __index); }

	bool is_edge_left(size_type __index) const
	{ return friend_algo::is_edge_left<>(*this, __index); }

	bool is_edge_right(size_type __index) const
	{ return friend_algo::is_edge_right<>(*this, __index); }

	bool is_edge_vertical(size_type __index) const
	{ return friend_algo::is_edge_vertical<>(*this, __index); }

	bool is_edge(size_type __index) const
	{ return friend_algo::is_edge(*this, __index); }

protected:
	node_type* data()
	{ return &_array[0]; }

	const node_type* data() const
	{ return &_array[0]; }
};

template<typename _Tp, std::size_t _Width, std::size_t _Height>
inline void swap(fixed_grid_cross<_Tp, _Width, _Height>& __one,
                 fixed_grid_cross<_Tp, _Width, _Height>& __two)
{ __one.swap(__two); }

}

}

namespace std {

/// tuple_size
template<typename _Tp>
class tuple_size;

/// tuple_element
template<std::size_t _Int, typename _Tp>
class tuple_element;

template<typename _Tp, std::size_t _Width, std::size_t _Height>
struct tuple_size<falcon::container::fixed_grid_cross<_Tp, _Width, _Height> >
{ static const std::size_t value = _Width * _Height; };

template<std::size_t _Int, typename _Tp, std::size_t _Width, std::size_t _Height>
struct tuple_element<_Int, falcon::container::fixed_grid_cross<_Tp, _Width, _Height> >
{
	static_assert(_Int - 1 > _Width * _Height, "invalid index");
	typedef _Tp type;
};

template<std::size_t _Int, typename _Tp, std::size_t _Width, std::size_t _Height>
inline typename tuple_element<_Int, falcon::container::fixed_grid_cross<_Tp, _Width, _Height> >::type&
get(falcon::container::fixed_grid_cross<_Tp, _Width, _Height>& __arr)
{ return __arr[_Int]; }

template<std::size_t _Int, typename _Tp, std::size_t _Width, std::size_t _Height>
inline const typename tuple_element<_Int, falcon::container::fixed_grid_cross<_Tp, _Width, _Height> >::type&
get(const falcon::container::fixed_grid_cross<_Tp, _Width, _Height>& __arr)
{ return __arr[_Int]; }

}

#endif
