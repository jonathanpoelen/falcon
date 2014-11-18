#include <test/test.hpp>
#include <falcon/lambda.hpp>
#include <falcon/container/fixed_grid_cross.hpp>
#include <falcon/container/grid_cross.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/algorithm/for_n.hpp>
#include "grid_cross.hpp"

#include <algorithm>

template<typename Grid>
void template_grid_test(Grid&);

void grid_cross_test()
{
	{
		falcon::container::fixed_grid_cross<int,3,3> grid;
		template_grid_test(grid);
	}
	PASSED();
	{
		falcon::container::grid_cross<int> grid(3,3);
		template_grid_test(grid);
	}
}

template<typename Grid>
void template_grid_test(Grid& grid)
{
	using namespace falcon::lambda::placeholders;
  using falcon::begin;
  using falcon::end;

	//falcon::generate(grid, ++falcon::make_lambda(0));
	std::stringstream ss;
	std::string s;
  {
    int i = 0;
    std::generate(begin(grid), end(grid), ++falcon::lambda::var(i));
	}
	PASSED();

  std::for_each(begin(grid), end(grid), ss << _1 << ',');
	s += "1,2,3,4,5,6,7,8,9,";
	PASSED();

	grid.back_to_first_each_line();
	ss << grid.is_back_to_first()
	<< ' ' << grid.is_back_to_first_each_line()
	<< ' ' << grid.is_back_to_first_column()
	<< ' ' << grid.is_back_to_first_each_column()
	<< std::endl;
	s += "1 1 0 0\n";
	PASSED();

	using falcon::algorithm::for_n;

	for_n(typename Grid::right_iterator(grid.front()),
					grid.size() , ss << ++_1 << ',');
	std::endl(ss);
	s += "2,3,4,5,6,7,8,9,10,\n";
	PASSED();

	for_n(typename Grid::left_iterator(&grid.back()),
					grid.size()*2 , ss << ++_1 << ',');
	std::endl(ss);
	s += "11,10,9,8,7,6,5,4,3,12,11,10,9,8,7,6,5,4,\n";
	PASSED();

	grid.back_to_first_each_column();
	ss << grid.is_back_to_first()
	<< ' ' << grid.is_back_to_first_each_line()
	<< ' ' << grid.is_back_to_first_column()
	<< ' ' << grid.is_back_to_first_each_column()
	<< std::endl;
	s += "1 1 1 1\n";
	PASSED();

	for_n(typename Grid::up_iterator(&grid.back()),
					grid.size() , ss << ++_1 << ',');
	std::endl(ss);
	s += "13,10,7,12,9,6,11,8,5,\n";
	PASSED();

	for_n(typename Grid::down_iterator(grid.front()),
					grid.size()*2 , ss << ++_1 << ',');
	std::endl(ss);
	s += "6,9,12,7,10,13,8,11,14,7,10,13,8,11,14,9,12,15,\n";
	PASSED();

	grid.edge_connect_horizontal();
	ss << grid.is_edge_connect_horizontal()
	<< ' ' << grid.is_edge_connect_vertical()
	<< std::endl;
	s += "1 0\n";
	PASSED();

	for_n(typename Grid::right_iterator(grid.front()),
					grid.size() , ss << ++_1 << ',');
	s += "8,9,10,11,12,13,14,15,16,";

	CHECK_EQUAL_VALUE(s, ss.str());
}

FALCON_TEST_TO_MAIN(grid_cross_test)
