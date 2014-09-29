#include <test/test.hpp>
#include <falcon/range/range.hpp>
#include "range.hpp"

void range_test()
{
	int i = 0;
	for (int& n: falcon::range(0,10)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i <= 10);
		++i;
	}
	CHECK_EQUAL_VALUE(i, 10);

	i = 0;
	for (int& n: falcon::range(0,12, 2)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i <= 12);
		i += 2;
	}
	CHECK_EQUAL_VALUE(i, 12);
}

FALCON_TEST_TO_MAIN(range_test)
