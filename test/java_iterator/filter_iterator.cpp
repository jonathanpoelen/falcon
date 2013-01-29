#include <vector>
#include <test/test.hpp>
#include <falcon/java_iterator/filter_iterator.hpp>
#include "filter_iterator.hpp"

void filter_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::java_iterator::make_filter_iterator<>(c.begin(), c.end(),
																													[](int i) {return i&1;}
																												 );
	//auto it = falcon::make_count_iterator<>(c.begin(), c.end());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(0, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.next());
	it.begin(c.begin()+1);
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(4, it.next());
	CHECK_EQUAL_VALUE(false, it.valid());
}

FALCON_TEST_TO_MAIN(filter_iterator_test)
