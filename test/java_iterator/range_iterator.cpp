#include <vector>
#include <test/test.hpp>
#include <falcon/java_iterator/range_iterator.hpp>
#include "range_iterator.hpp"

void range_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::java_iterator::make_range_iterator<>(c);
	//auto it = falcon::make_java_iterator<>(c.begin(), c.end());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(0, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(1, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(3, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(4, it.next());
	CHECK_EQUAL_VALUE(false, it.valid());
	it = c.end();
	it.prev();
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(4, it.prev());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(3, it.prev());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.prev());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(1, it.prev());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(0, it.prev());
}
FALCON_TEST_TO_MAIN(range_iterator_test)
