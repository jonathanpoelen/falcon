#include <test/test.hpp>
#include <falcon/algorithm/reduce.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/container/range_access.hpp>
#include "reduce.hpp"

void reduce_test(/*int argc, char** argv*/)
{
	using falcon::algorithm::reduce;
	using falcon::begin;
	using falcon::end;
	using falcon::plus;

	int array[] = {1,2,3,4,5};
	CHECK_EQUAL_VALUE(15, reduce(begin(array), end(array), plus<int>()));
	CHECK_EQUAL_VALUE(15, reduce<>(array, plus<int>()));
	CHECK_EQUAL_VALUE(115, reduce<>(begin(array), end(array), plus<int>(), 100));
	CHECK_EQUAL_VALUE(20, reduce<>(array, plus<int>(), 5));
}

FALCON_TEST_TO_MAIN(reduce_test)
