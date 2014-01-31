#include <test/test.hpp>
#include <falcon/range/irange.hpp>
#include "irange.hpp"

void irange_test()
{
	int i = 0;
	for (int& n: falcon::irange(0,10)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i <= 10);
		++i;
	}
	CHECK_EQUAL_VALUE(i, 10);

	i = 0;
	for (int& n: falcon::irange(0,12, 2)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i <= 12);
		i += 2;
	}
	CHECK_EQUAL_VALUE(i, 12);
}

FALCON_TEST_TO_MAIN(irange_test)
