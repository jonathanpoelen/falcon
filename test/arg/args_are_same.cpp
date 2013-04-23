#include <test/test.hpp>
#include <falcon/arg/args_are_same.hpp>
#include "args_are_same.hpp"

void args_are_same_test()
{
	using falcon::args_are_same;

	STATIC_CHECK_VALUE(true, args_are_same<int,int,int,int,int>);
	STATIC_CHECK_VALUE(false, args_are_same<int*,int>);
	STATIC_CHECK_VALUE(false, args_are_same<int*,int&>);
	STATIC_CHECK_VALUE(false, args_are_same<int*,int[5]>);
	STATIC_CHECK_VALUE(false, args_are_same<int*,int,int>);
	STATIC_CHECK_VALUE(false, args_are_same<int*,int&,int&>);
	STATIC_CHECK_VALUE(false, args_are_same<int*,int[5],int*>);
}
FALCON_TEST_TO_MAIN(args_are_same_test)
