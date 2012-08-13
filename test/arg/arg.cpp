#include <test/test.hpp>
#include <falcon/arg/arg.hpp>
#include "arg.hpp"

void arg_test()
{
	using falcon::arg_size;
	using falcon::arg_element;
	using falcon::arg;

	STATIC_CHECK_VALUE(5, arg_size<int,int,int,int,int>);

	CHECK_TYPE(int, arg_element<0, int, float*, const double&>);
	CHECK_TYPE(float*, arg_element<1, int, float*, const double&>);
	CHECK_TYPE(const double&, arg_element<2, int, float*, const double&>);

	CHECK_EQUAL_VALUE(1, arg<0>(1,2,3));
	CHECK_EQUAL_VALUE(2, arg<1>(1,2,3));
	CHECK_EQUAL_VALUE(3, arg<2>(1,2,3));

	int i = 2;
	++arg<1>(1,i,3);
	CHECK_EQUAL_VALUE(3, i);
}
FALCON_TEST_TO_MAIN(arg_test)
