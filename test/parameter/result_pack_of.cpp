#include <test/test.hpp>
#include <falcon/parameter/result_pack_of.hpp>
#include "result_pack_of.hpp"

struct _Result_pack_of_test
{
	double operator()(double, int = 5);
};

void result_pack_of_test()
{
	typedef falcon::parameter::result_of<
		_Result_pack_of_test,
		falcon::parameter_pack<int>
	> result_pack;
	CHECK_TYPE(double, result_pack);
}

FALCON_TEST_TO_MAIN(result_pack_of_test)
