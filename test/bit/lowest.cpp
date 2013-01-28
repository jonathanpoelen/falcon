#include <test/test.hpp>
#include <falcon/bit/lowest.hpp>
#include "lowest.hpp"

void lowest_test()
{
	CHECK_EQUAL_VALUE(falcon::bit::clear_lowest<>(0), 0);
	CHECK_EQUAL_VALUE(falcon::bit::clear_lowest<>(5), 4);
	CHECK_EQUAL_VALUE(falcon::bit::clear_lowest<>(7), 6);
	CHECK_EQUAL_VALUE(falcon::bit::clear_lowest<>(12), 8);

	CHECK_EQUAL_VALUE(falcon::bit::insert_lowest<>(0), 1);
	CHECK_EQUAL_VALUE(falcon::bit::insert_lowest<>(1), 3);
	CHECK_EQUAL_VALUE(falcon::bit::insert_lowest<>(4), 5);

	CHECK_EQUAL_VALUE(falcon::bit::lowest<>(0), 0);
	CHECK_EQUAL_VALUE(falcon::bit::lowest<>(5), 1);
	CHECK_EQUAL_VALUE(falcon::bit::lowest<>(8), 8);
	CHECK_EQUAL_VALUE(falcon::bit::lowest<>(24), 8);
}

FALCON_TEST_TO_MAIN(lowest_test)
