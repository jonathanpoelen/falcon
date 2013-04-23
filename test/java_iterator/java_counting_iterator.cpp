#include <vector>
#include <test/test.hpp>
#include <falcon/java_iterator/java_counting_iterator.hpp>
#include "java_counting_iterator.hpp"

void java_counting_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::java_iterator::make_java_counting_iterator<>(c.begin(),3);
	//auto it = falcon::make_count_iterator<>(c.begin(), c.end());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(0, it.next()++);
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(1, it.next()++);
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.next()++);
	CHECK_EQUAL_VALUE(false, it.valid());
	it = c.begin();
	it.count(2);
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(1, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.next());
	CHECK_EQUAL_VALUE(false, it.valid());

}
FALCON_TEST_TO_MAIN(java_counting_iterator_test)
