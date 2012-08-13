#include <test/test.hpp>
#include <falcon/type_traits/scalar.hpp>
#include "scalar.hpp"

void scalar_test()
{
	using falcon::size_in_scalar;
	using falcon::get_scalar;
	using falcon::get_integral;
	using falcon::get_floating_point;

	STATIC_CHECK_VALUE(true, size_in_scalar<1>);
	STATIC_CHECK_VALUE(false, size_in_scalar<3>);
	STATIC_CHECK_VALUE(false, size_in_scalar<300>);
	STATIC_CHECK_VALUE(true, size_in_scalar<sizeof(long)>);

	CHECK_TYPE(long, get_integral<sizeof(long)>);
	CHECK_TYPE(char, get_integral<1>);
	CHECK_TYPE(int, get_integral<4>);

	CHECK_TYPE(float, get_floating_point<sizeof(float)>);
}
FALCON_TEST_TO_MAIN(scalar_test)
