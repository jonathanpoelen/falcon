#include <falcon/algorithm/dichotomous.hpp>
#include <array>
#include "../test.hpp"
#include "dichotomous.hpp"

void dichotomous_test()
{
	using falcon::dichotomous_find;

	std::array<int, 10> arr{{0,1,2,5,7,9,10,11,15,20}};
	auto first = arr.begin();
	auto last = arr.end();

	CHECK_EQUAL_VALUE(last, dichotomous_find(first, last, -1));
	CHECK_EQUAL_VALUE(first, dichotomous_find(first, last, 0));
	CHECK_EQUAL_VALUE(last-1, dichotomous_find(first, last, 20));
	CHECK_EQUAL_VALUE(last, dichotomous_find(first, last, 30));
	CHECK_EQUAL_VALUE(first+6, dichotomous_find(first, last, 10));
}

FALCON_TEST_TO_MAIN(dichotomous_test)
