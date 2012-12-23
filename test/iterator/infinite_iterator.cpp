#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/infinite_iterator.hpp>
#include "infinite_iterator.hpp"

void infinite_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::iterator::make_infinite_iterator(c);
	//auto it = falcon::make_infinite_iterator(c, c.begin());
	//auto it = falcon::make_infinite_iterator(c.begin(), c.end());
	//auto it = falcon::make_infinite_iterator(c.begin(), c.begin(), c.end());
	CHECK_EQUAL_VALUE(0, *it);
	CHECK_EQUAL_VALUE(1, *++it);
	CHECK_EQUAL_VALUE(2, *++it);
	CHECK_EQUAL_VALUE(3, *++it);
	CHECK_EQUAL_VALUE(4, *++it);
	CHECK_EQUAL_VALUE(0, *++it);
	CHECK_EQUAL_VALUE(1, *++it);
	it = c.begin();
	CHECK_EQUAL_VALUE(0, *it);
	CHECK_EQUAL_VALUE(4, *--it);
	CHECK_EQUAL_VALUE(3, *--it);
	CHECK_EQUAL_VALUE(2, *--it);
	CHECK_EQUAL_VALUE(1, *--it);
	CHECK_EQUAL_VALUE(0, *--it);

	CHECK_EQUAL_VALUE(0, *(it+=5));
	CHECK_EQUAL_VALUE(1, *(it+=6));
	CHECK_EQUAL_VALUE(4, *(it+=13));

	CHECK_EQUAL_VALUE(4, *(it-=5));
	CHECK_EQUAL_VALUE(3, *(it-=6));
	CHECK_EQUAL_VALUE(1, *(it-=12));
}
FALCON_TEST_TO_MAIN(infinite_iterator_test)
