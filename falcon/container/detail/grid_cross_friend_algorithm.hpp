#ifndef _DETAIL_CONTAINER_GRID_CROSS_FRIEND_ALGORITHM_HPP
#define _DETAIL_CONTAINER_GRID_CROSS_FRIEND_ALGORITHM_HPP

#include <type_traits>

namespace falcon {
namespace container {
namespace detail {

struct grid_cross_friend_algorithm
{
	template<typename _GridCross>
	static void init(_GridCross& grid)
	{
		auto it = grid.begin();
		auto end = it + grid.size();
		auto it2 = it + grid.width();
		while (it2 != end){
			it->_M_link().left = 0;
			for (typename _GridCross::size_type endx = grid.width(); --endx; ++it, ++it2){
				down(it, it2);
				right(it, it+1);
			}
			it->_M_link().right = 0;
			down(it, it2);
			++it;
			++it2;
		}
		it->_M_link().left = 0;
		for (--end; it != end; ++it){
			right(it, it+1);
		}
		it->_M_link().right = 0;
	}

	template<typename _Node>
	static inline void down(_Node* n, _Node* n2)
	{
		n->_M_link().down = n2;
		n2->_M_link().up = n;
	}

	template<typename _Node>
	static inline void right(_Node* n, _Node* n2)
	{
		n->_M_link().right = n2;
		n2->_M_link().left = n;
	}

	template<typename _Node>
	static inline void down(_Node* n, _Node* n2, int)
	{
		n->_M_link().down = 0;
		n2->_M_link().up = 0;
	}

	template<typename _Node>
	static inline void right(_Node* n, _Node* n2, int)
	{
		n->_M_link().right = 0;
		n2->_M_link().left = 0;
	}

	template<typename _Node>
	static inline void down(_Node& n, _Node& n2)
	{
		n->_M_link().down = &*n2;
		n2->_M_link().up = &*n;
	}

#if __cplusplus >= 201103L
	template<typename _Node>
	static inline typename std::enable_if<std::is_rvalue_reference<_Node &&>::value, void>::type down(_Node&& n, _Node&& n2)
	{
		n->_M_link().down = &*n2;
		n2->_M_link().up = &*n;
	}

	template<typename _Node>
	static inline typename std::enable_if<std::is_rvalue_reference<_Node &&>::value, void>::type right(_Node n, _Node n2)
	{
		n->_M_link().right = &*n2;
		n2->_M_link().left = &*n;
	}
#endif

	template<typename _Node>
	static inline void down(_Node n, _Node n2, int)
	{
		n->_M_link().down = 0;
		n2->_M_link().up = 0;
	}

	template<typename _Node>
	static inline void right(_Node n, _Node n2, int)
	{
		n->_M_link().right = 0;
		n2->_M_link().left = 0;
	}

	template<typename _GridCross>
	static bool is_back_to_first(const _GridCross& grid)
	{ return equal(grid.front().left(), back_iterator(grid)); }

	template<typename _GridCross>
	static void back_to_first(_GridCross& grid, bool connect)
	{
		if (connect) {
			right(back_iterator(grid), grid.begin());
		} else {
			right(back_iterator(grid), grid.begin(), 0);
		}
	}

	template<typename _GridCross>
	static bool is_back_to_first_each_line(const _GridCross& grid)
	{ auto it = back_line_iterator(grid); return equal(it->right(), it+1); }

	template<typename _GridCross>
	static void back_to_first_each_line(_GridCross& grid, bool connect)
	{
		for (auto it = back_line_iterator(grid), end = back_iterator(grid); it != end; it += grid.width()){
			if (connect)
				right(it, it+1);
			else
				right(it, it+1, 0);
		}
		back_to_first(grid, connect);
	}

	template<typename _GridCross>
	static bool is_back_to_first_column(const _GridCross& grid)
	{ return equal(grid.front().up(), back_iterator(grid)); }

	template<typename _GridCross>
	static void back_to_first_column(_GridCross& grid, bool connect)
	{
		if (connect) {
			down(back_iterator(grid), grid.begin());
		} else {
			down(back_iterator(grid), grid.begin(), 0);
		}
	}

protected:
	template<typename _T>
	inline static bool equal(_T a, _T b)
	{ return a == b; }

	template<typename _T, typename _U>
	inline static bool equal(_T a, _U b)
	{ return a ? *a == *b : false; }

public:
	template<typename _GridCross>
	static bool is_back_to_first_each_column(const _GridCross& grid)
	{ return equal(grid.front().up(), back_iterator(grid)); }

	template<typename _GridCross>
	static void back_to_first_each_column(_GridCross& grid, bool connect)
	{
		for (auto it = grid.begin()+1, it2 = it + (grid.size() - (grid.width() + 1)), end = back_line_iterator(grid, it); it != end; ++it, ++it2){
			if (connect)
				down(it2, it);
			else
				down(it2, it, 0);
		}
		back_to_first_column(grid, connect);
	}

	template<typename _GridCross>
	static bool is_edge_connect_horizontal(const _GridCross& grid)
	{ return equal(grid.begin()->up(), grid.begin() + (grid.size() - grid.width())); }

	template<typename _GridCross>
	static void edge_connect_horizontal(_GridCross& grid, bool connect)
	{
		for (auto it = grid.begin(), it2 = it + (grid.size() - grid.width()), end = it + grid.width(); it != end; ++it, ++it2){
			if (connect)
				down(it2, it);
			else
				down(it2, it, 0);
		}
	}

	template<typename _GridCross>
	static bool is_edge_connect_vertical(const _GridCross& grid)
	{ return equal(grid.begin()->left(), back_line_iterator(grid)); }

	template<typename _GridCross>
	static void edge_connect_vertical(_GridCross& grid, bool connect)
	{
		for (auto it = grid.begin(), end = it + (grid.size() - grid.width()); it != end; it += grid.width()){
			if (connect)
				right(back_line_iterator(grid, it), it);
			else
				right(back_line_iterator(grid, it), it, 0);
		}
	}

	template<typename _GridCross>
	static void edge_connect(_GridCross& grid, bool connect)
	{
		edge_connect_horizontal(grid, connect);
		edge_connect_vertical(grid, connect);
	}

	template<typename _GridCross>
	static bool is_edge_up(const _GridCross& grid, typename _GridCross::size_type index)
	{ return 0 <= index && index < grid.width(); }

	template<typename _GridCross>
	static bool is_edge_down(const _GridCross& grid, typename _GridCross::size_type index)
	{ return grid.size() - grid.width() <= index && index < grid.size(); }

	template<typename _GridCross>
	static bool is_edge_horizontal(const _GridCross& grid, typename _GridCross::size_type index)
	{ return is_edge_up(index) || is_edge_down(index); }

	template<typename _GridCross>
	static bool is_edge_left(const _GridCross& grid, typename _GridCross::size_type index)
	{ return 0 == index % grid.height(); }

	template<typename _GridCross>
	static bool is_edge_right(const _GridCross& grid, typename _GridCross::size_type index)
	{ return grid.width() - 1 == index % grid.height(); }

	template<typename _GridCross>
	static bool is_edge_vertical(const _GridCross& grid, typename _GridCross::size_type index)
	{ int m = index % grid.height(); return m == 0 || m == grid.width() - 1; }

	template<typename _GridCross>
	static bool is_edge(const _GridCross& grid, typename _GridCross::size_type index)
	{ return is_edge_horizontal(index) || is_edge_vertical(index); }

	template<typename _GridCross>
	static typename _GridCross::iterator back_iterator(_GridCross& grid)
	{ return grid.size() ? grid.end() - 1 : grid.end(); }

	template<typename _GridCross>
	static typename _GridCross::const_iterator back_iterator(const _GridCross& grid)
	{ return grid.size() ? grid.end() - 1 : grid.end(); }

	template<typename _GridCross>
	static typename _GridCross::iterator back_line_iterator(_GridCross& grid, typename _GridCross::iterator it)
	{ return it + (grid.width() - 1); }

	template<typename _GridCross>
	static typename _GridCross::const_iterator back_line_iterator(const _GridCross& grid, typename _GridCross::const_iterator it)
	{ return it + (grid.width() - 1); }

	template<typename _GridCross>
	static typename _GridCross::iterator back_line_iterator(_GridCross& grid)
	{ return grid.begin() + (grid.width() - 1); }

	template<typename _GridCross>
	static typename _GridCross::const_iterator back_line_iterator(const _GridCross& grid)
	{ return grid.begin() + (grid.width() - 1); }
};

}
}
}

#endif