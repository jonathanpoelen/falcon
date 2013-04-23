#include <test/test.hpp>
#include <falcon/functional/decremental_generator.hpp>
#include <falcon/functional/incremental_generator.hpp>
#include "generator.hpp"

void generator_test()
{
	{
		falcon::decremental_generator<int> g(5);
		CHECK_EQUAL_VALUE(5, g());
		CHECK_EQUAL_VALUE(4, g());
		CHECK_EQUAL_VALUE(3, g());
		CHECK_EQUAL_VALUE(2, g());
		CHECK_EQUAL_VALUE(1, g());
		CHECK_EQUAL_VALUE(0, g());
		CHECK_EQUAL_VALUE(-1, g());
	}
	{
		falcon::predecremental_generator<int> g(4);
		CHECK_EQUAL_VALUE(3, g());
		CHECK_EQUAL_VALUE(2, g());
		CHECK_EQUAL_VALUE(1, g());
		CHECK_EQUAL_VALUE(0, g());
		CHECK_EQUAL_VALUE(-1, g());
	}
	{
		falcon::incremental_generator<int> g;
		CHECK_EQUAL_VALUE(0, g());
		CHECK_EQUAL_VALUE(1, g());
		CHECK_EQUAL_VALUE(2, g());
	}
	{
		falcon::preincremental_generator<int> g(-1);
		CHECK_EQUAL_VALUE(0, g());
		CHECK_EQUAL_VALUE(1, g());
		CHECK_EQUAL_VALUE(2, g());
	}
}

FALCON_TEST_TO_MAIN(generator_test)
