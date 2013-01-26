#include <vector>
#include <test/test.hpp>
#include <falcon/java_iterator/stepping_iterator.hpp>
#include "stepping_iterator.hpp"

void stepping_iterator_test()
{
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::java_iterator::make_stepping_iterator<>(c, 2);
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(0, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(2, it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE(4, it.next());
	CHECK_EQUAL_VALUE(false, it.valid());

}
FALCON_TEST_TO_MAIN(stepping_iterator_test)
