#include <test/test.hpp>
#include <falcon/functional/compose.hpp>
#include <falcon/functional/operators.hpp>
#include "compose.hpp"

void compose_test()
{
	typedef falcon::increment<int> increment;
	typedef falcon::dereference<int*> pointer;
	typedef falcon::unary_compose<increment, pointer> unary1;

	int i = 5;
	int * p = &i;

	CHECK_EQUAL_VALUE(unary1()(p), 6);
	CHECK_EQUAL_VALUE(falcon::compose1(increment(), pointer())(p), 7);
}

FALCON_TEST_TO_MAIN(compose_test)
