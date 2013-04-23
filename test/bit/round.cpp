#include <test/test.hpp>
#include <falcon/bit/round.hpp>
#include "round.hpp"

void round_test()
{
	CHECK_EQUAL_VALUE(falcon::bit::round<>(15), 16);
	CHECK_EQUAL_VALUE(falcon::bit::round<>(16), 16);
	CHECK_EQUAL_VALUE(falcon::bit::round<>(17), 32);
}

FALCON_TEST_TO_MAIN(round_test)
