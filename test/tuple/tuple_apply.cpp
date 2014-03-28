#include <tuple>
#include <test/test.hpp>
#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/functional/operators.hpp>
#include "tuple_apply.hpp"

struct S3
{
	long operator()(int n, long n2, long n3) const
	{
		return (n3 + n) / n2;
	}
};

void tuple_apply_test()
{
	typedef std::tuple<int, int> tuple2_type;
	typedef std::tuple<int, int, long> tuple3_type;
	{
		tuple2_type t(1,2);

		CHECK_EQUAL_VALUE(3, falcon::tuple_apply(falcon::plus<int>(), t));
		falcon::plus<int> f;
		CHECK_EQUAL_VALUE(3, falcon::tuple_apply(f, t));
		CHECK_EQUAL_VALUE(3, falcon::tuple_apply(falcon::plus<int>(), tuple2_type(1,2)));
	}
	{
		tuple3_type t(1,2,60);

		CHECK_EQUAL_VALUE(30, falcon::tuple_apply(S3(), t));
		CHECK_EQUAL_VALUE(0, falcon::tuple_apply(falcon::parameter_index<0,2,1>(), S3(), t));
		CHECK_EQUAL_VALUE(0, falcon::tuple_apply(falcon::parameter_index<0,2,1>(), S3(), tuple3_type(1,2,60)));
	}
}

FALCON_TEST_TO_MAIN(tuple_apply_test)
