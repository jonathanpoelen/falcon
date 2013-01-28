#include <test/test.hpp>
#include <falcon/bit/count.hpp>
#include "count.hpp"

void count_test()
{
	CHECK_EQUAL_VALUE(falcon::bit::count<>(0), 0);
	CHECK_EQUAL_VALUE(falcon::bit::count<>(0x80), 1);
	CHECK_EQUAL_VALUE(falcon::bit::count<>(0xf0), 4);
	CHECK_EQUAL_VALUE(falcon::bit::count<>(0xff), 8);
	CHECK_EQUAL_VALUE(falcon::bit::count<>(0x88), 2);
}

FALCON_TEST_TO_MAIN(count_test)
