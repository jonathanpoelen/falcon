#include <vector>
#include <test/test.hpp>
#include <falcon/java_iterator/filter_iterator.hpp>
#include "filter_iterator.hpp"

void filter_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::java_iterator::make_filter_iterator<>(
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	[](int i) {return i&1;},
#endif
	c);
	//auto it = falcon::make_count_iterator<>(c.begin(), c.end());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(1, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	it = c.begin();
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(1, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(3, it.next());
	CHECK_EQUAL_VALUE(false, it.valid());

}
FALCON_TEST_TO_MAIN(filter_iterator_test)
