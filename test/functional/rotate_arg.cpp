#include <test/test.hpp>
#include <falcon/functional/rotate_arg.hpp>
#include "rotate_arg.hpp"

void rotate_arg_test()
{
	int a = 1, b = 2, c = 3, d = 4;
	falcon::rotate_arg(a,b,c,d);
	CHECK_EQUAL_VALUE(4, a);
	CHECK_EQUAL_VALUE(1, b);
	CHECK_EQUAL_VALUE(2, c);
	CHECK_EQUAL_VALUE(3, d);
	falcon::rotate_arg<2>(a,b,c,d);
	CHECK_EQUAL_VALUE(2, a);
	CHECK_EQUAL_VALUE(3, b);
	CHECK_EQUAL_VALUE(4, c);
	CHECK_EQUAL_VALUE(1, d);
	falcon::rotate_arg<-3>(a,b,c,d);
	CHECK_EQUAL_VALUE(1, a);
	CHECK_EQUAL_VALUE(2, b);
	CHECK_EQUAL_VALUE(3, c);
	CHECK_EQUAL_VALUE(4, d);

	int e = 5;
	falcon::rotate_arg(a,b,c,d,e);
	CHECK_EQUAL_VALUE(5, a);
	CHECK_EQUAL_VALUE(1, b);
	CHECK_EQUAL_VALUE(2, c);
	CHECK_EQUAL_VALUE(3, d);
	CHECK_EQUAL_VALUE(4, e);
	falcon::rotate_arg<2>(a,b,c,d,e);
	CHECK_EQUAL_VALUE(3, a);
	CHECK_EQUAL_VALUE(4, b);
	CHECK_EQUAL_VALUE(5, c);
	CHECK_EQUAL_VALUE(1, d);
	CHECK_EQUAL_VALUE(2, e);
	falcon::rotate_arg<-3>(a,b,c,d,e);
	CHECK_EQUAL_VALUE(1, a);
	CHECK_EQUAL_VALUE(2, b);
	CHECK_EQUAL_VALUE(3, c);
	CHECK_EQUAL_VALUE(4, d);
	CHECK_EQUAL_VALUE(5, e);

	falcon::rotate_arg<1>(a,b);
	CHECK_EQUAL_VALUE(2, a);
	CHECK_EQUAL_VALUE(1, b);

	falcon::rotate_arg<-3>(a,b);
	CHECK_EQUAL_VALUE(1, a);
	CHECK_EQUAL_VALUE(2, b);

	falcon::rotate_arg<0>(a);
	CHECK_EQUAL_VALUE(1, a);
}
FALCON_TEST_TO_MAIN(rotate_arg_test)
