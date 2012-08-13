#include "../test.hpp"
#include <falcon/arg/result_range_of.hpp>
#include "result_range_of.hpp"

struct _arg_range_test
{
	int operator()(int);
	float operator()(float);
	long operator()(float, int);
	double operator()(double);
	void operator()(long);
	void operator()();
	void operator()(short, int = 0);
};

void result_range_of_test()
{
	using falcon::result_range_of;

	CHECK_TYPE(int, result_range_of<0,1, _arg_range_test(int,float, double)>);
	CHECK_TYPE(double, result_range_of<2,1, _arg_range_test(int,float, double)>);
	///NOTE invalid range: CHECK_TYPE(void, result_range_of<2,1, _arg_range_test(long)>);
	///NOTE invalid range: CHECK_TYPE(void, result_range_of<2,1, _arg_range_test(float, int)>);
	CHECK_TYPE(long, result_range_of<0,2, _arg_range_test(float, int)>);
	CHECK_TYPE(float, result_range_of<1,1, _arg_range_test(int, float)>);
	///NOTE invalid range: CHECKNO_TYPE(long, result_range_of<0,5, _arg_range_test(float, int)>);
	CHECK_TYPE(void, result_range_of<0,1, _arg_range_test(short)>);
}
FALCON_TEST_TO_MAIN(result_range_of_test)
