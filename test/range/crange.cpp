#include <test/test.hpp>
#include <falcon/range/crange.hpp>
#include "crange.hpp"

void crange_test()
{
	int i = 0;
	for (int& n: falcon::crange(0,10)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i < 12);
		++i;
	}
	CHECK_EQUAL_VALUE(12, i);

	i = 0;
	for (int& n: falcon::crange(0,10, 2)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i <= 10);
		i += 2;
	}
	CHECK_EQUAL_VALUE(i, 12);
}
FALCON_TEST_TO_MAIN(crange_test)
