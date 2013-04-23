#include <test/test.hpp>
#include <falcon/algorithm/algorithm.hpp>
#include "algorithm.hpp"

void algorithm_test()
{
	int arr[2] = {1,2};
	int *parr = arr;
	CHECK_EQUAL_VALUE(parr+1, falcon::algorithm::find<>(arr, 2));

}
FALCON_TEST_TO_MAIN(algorithm_test)
