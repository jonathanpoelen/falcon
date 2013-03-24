#include <test/test.hpp>
#include <falcon/range/integer_range.hpp>
#include "integer_range.hpp"

void integer_test()
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

	i = 10;
	for (int& n: falcon::reverse_irange(10,0)){
		CHECK_EQUAL_VALUE(--i, --n);
		CHECK(i > -2);
		--i;
	}
	CHECK_EQUAL_VALUE(-2, i);

	i = 10;
	for (int& n: falcon::reverse_irange(10,0, 2)){
		CHECK_EQUAL_VALUE(++i, ++n);
		CHECK(i >= 0);
		i -= 2;
	}
	CHECK_EQUAL_VALUE(i, -1);
}
FALCON_TEST_TO_MAIN(integer_test)
