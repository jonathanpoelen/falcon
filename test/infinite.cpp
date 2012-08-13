#include <falcon/infinite.hpp>
#include <test/test.hpp>
#include "infinite.hpp"

void infinite_test()
{
	{
		falcon::infinite<int> n(0,4);
		CHECK_EQUAL_VALUE(0, n);
		CHECK_EQUAL_VALUE(1, ++n);
		CHECK_EQUAL_VALUE(2, ++n);
		CHECK_EQUAL_VALUE(3, ++n);
		CHECK_EQUAL_VALUE(0, ++n);
		CHECK_EQUAL_VALUE(1, ++n);
		CHECK_EQUAL_VALUE(2, ++n);
		n = 1;
		CHECK_EQUAL_VALUE(1, n);
		CHECK_EQUAL_VALUE(0, --n);
		CHECK_EQUAL_VALUE(3, --n);
		CHECK_EQUAL_VALUE(2, --n);
		CHECK_EQUAL_VALUE(1, --n);
	}
}
FALCON_GROUP_TEST_TO_MAIN(infinite_test)
