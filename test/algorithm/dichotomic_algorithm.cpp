#include <falcon/algorithm/dichotomic_algorithm.hpp>
#include <array>
#include "../test.hpp"
#include "dichotomic_algorithm.hpp"

void dichotomic_algorithm_test()
{
	using falcon::dichotomic_find;
	using falcon::dichotomic_lower_bound;

	std::array<int, 10> arr{{0,1,2,5,7,9,10,11,15,20}};
	auto first = arr.begin();
	auto last = arr.end();

	CHECK_EQUAL_VALUE(first, dichotomic_lower_bound(first, last, -1));
	CHECK_EQUAL_VALUE(first, dichotomic_lower_bound(first, last, 0));
	CHECK_EQUAL_VALUE(last-1, dichotomic_lower_bound(first, last, 20));
	CHECK_EQUAL_VALUE(last, dichotomic_lower_bound(first, last, 30));

	CHECK_EQUAL_VALUE(last, dichotomic_find(first, last, -1));
	CHECK_EQUAL_VALUE(first, dichotomic_find(first, last, 0));
	CHECK_EQUAL_VALUE(last-1, dichotomic_find(first, last, 20));
	CHECK_EQUAL_VALUE(last, dichotomic_find(first, last, 30));
	CHECK_EQUAL_VALUE(first+6, dichotomic_find(first, last, 10));
}
FALCON_TEST_TO_MAIN(dichotomic_algorithm_test)
