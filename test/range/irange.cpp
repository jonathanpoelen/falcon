#include <test/test.hpp>
#include <falcon/range/irange.hpp>
#include "irange.hpp"

void irange_test()
{
	int i = 0;
	for (int& n: falcon::irange(0,10)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i < 12);
		++i;
	}
	CHECK_EQUAL_VALUE(12, i);

	i = 0;
	for (int& n: falcon::irange(0,10, 2)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i <= 10);
		i += 2;
	}
	CHECK_EQUAL_VALUE(i, 12);
}
FALCON_TEST_TO_MAIN(irange_test)
