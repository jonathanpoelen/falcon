#include <vector>
#include <test/test.hpp>
#include <falcon/java_iterator/java_iterator.hpp>
#include "java_iterator.hpp"

void java_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::java_iterator::make_java_iterator<>(c);
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
	it.begin(c.end());
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
FALCON_TEST_TO_MAIN(java_iterator_test)
