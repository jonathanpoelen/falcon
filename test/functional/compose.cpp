#include <test/test.hpp>
#include <falcon/functional/compose.hpp>
#include <falcon/functional/operators.hpp>
#include "compose.hpp"

void compose_test()
{
	typedef falcon::increment<int> unary1;
	typedef falcon::pointer<int*> unary2;
	typedef falcon::unary_compose<unary1, unary2> unary3;

	int i = 5;
	int * p = &i;

	CHECK_EQUAL_VALUE(unary3()(p), 6);
}

FALCON_TEST_TO_MAIN(compose_test)
