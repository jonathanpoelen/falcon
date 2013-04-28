#include <test/test.hpp>
#include <cstdint>
#include "cut_and_place.hpp"

// #undef __cplusplus >= 201103L
#include <falcon/functional/cut_and_place.hpp>

void cut_and_place_test()
{
	uint16_t a,b,c;
	uint64_t v = 0xf1f2f3f4f5f6f7f8;

	falcon::cut_and_place<uint16_t, 2>(v, a);
	CHECK_EQUAL_VALUE(0xf7f8, a);
	a = 0;
	falcon::cut_and_place<uint16_t, 2>(v, a,b,c);
	CHECK_EQUAL_VALUE(0xf7f8, a);
	CHECK_EQUAL_VALUE(0xf5f6, b);
	CHECK_EQUAL_VALUE(0xf3f4, c);
}

FALCON_TEST_TO_MAIN(cut_and_place_test)
