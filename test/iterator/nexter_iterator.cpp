#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include "nexter_iterator.hpp"

void nexter_iterator_test()
{
	typedef std::vector<int> container_type;
	typedef typename container_type::iterator iterator;
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::iterator::make_nexter_iterator<>(c.begin(),
																										 [](iterator&__it){return ++__it;}
	);
	auto end = falcon::iterator::make_nexter_iterator<>(c.end(), it.nexter());

	CHECK_EQUAL_VALUE(true, it != end);
	CHECK_EQUAL_VALUE(0, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(1, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(2, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(3, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(4, (*it)++);
	CHECK_EQUAL_VALUE(false, ++it != end);
	it = c.begin();
	CHECK_EQUAL_VALUE(true, it != end);
	CHECK_EQUAL_VALUE(1, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(2, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(3, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(4, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(5, *it);
	CHECK_EQUAL_VALUE(false, ++it != end);

}
FALCON_TEST_TO_MAIN(nexter_iterator_test)
