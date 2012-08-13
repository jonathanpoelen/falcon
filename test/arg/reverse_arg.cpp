#include <test/test.hpp>
#include <falcon/arg/reverse_arg.hpp>
#include "reverse_arg.hpp"

void reverse_arg_test()
{
	using falcon::reverse_arg;

	typedef falcon::parameter_pack<double, float, int> pack_type;
	CHECK_TYPE(pack_type, reverse_arg<int,float, double>);
}
FALCON_TEST_TO_MAIN(reverse_arg_test)
