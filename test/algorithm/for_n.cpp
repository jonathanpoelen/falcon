#include <falcon/functional/operators.hpp>
#include <falcon/algorithm/for_n.hpp>
#include <vector>
#include "../test.hpp"
#include "for_n.hpp"

void for_n_test()
{
	using falcon::for_n;

	std::vector<int> vector(3,3);
	for_n(vector.begin(), 2, falcon::increment<>());
	CHECK_EQUAL_VALUE(4, vector[0]);
	CHECK_EQUAL_VALUE(4, vector[1]);
	CHECK_EQUAL_VALUE(3, vector[2]);
	for_n(vector.begin()+1, 1, falcon::increment<>());
	CHECK_EQUAL_VALUE(4, vector[0]);
	CHECK_EQUAL_VALUE(5, vector[1]);
	CHECK_EQUAL_VALUE(3, vector[2]);

	int array[3] = {3,3,3};
	for_n(&array[0], 1, falcon::increment<>());
	CHECK_EQUAL_VALUE(4, array[0]);
	CHECK_EQUAL_VALUE(3, array[1]);
	CHECK_EQUAL_VALUE(3, array[2]);

}
FALCON_TEST_TO_MAIN(for_n_test)
