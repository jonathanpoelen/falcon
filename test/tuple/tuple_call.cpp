#include <test/test.hpp>
#include <falcon/tuple/tuple_call.hpp>
#include <falcon/functional/operators.hpp>
#include "tuple_call.hpp"

struct S3
{
	long operator()(int n, long n2, long n3)
	{
		return (n3 + n) / n2;
	}
};

void tuple_call_test()
{
	typedef std::tuple<int, int> tuple2_type;
	typedef std::tuple<int, int, long> tuple3_type;
	{
		tuple2_type t(1,2);

		CHECK_EQUAL_VALUE(3, falcon::tuple_call<>(falcon::plus<int>(), t));
	}
	{
		tuple3_type t(1,2,60);

		CHECK_EQUAL_VALUE(30, falcon::tuple_call<>(S3(), t));
		CHECK_EQUAL_VALUE(0, falcon::tuple_call<>(falcon::parameter_index<0,2,1>(), S3(), t));
	}
}

FALCON_TEST_TO_MAIN(tuple_call_test)
