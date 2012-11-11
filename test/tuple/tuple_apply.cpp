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

		CHECK_EQUAL_VALUE(3, falcon::tuple_apply<>(t, falcon::plus<int>()));
	}
	{
		tuple3_type t(1,2,60);

		CHECK_EQUAL_VALUE(30, falcon::tuple_apply<>(t, S3()));
		CHECK_EQUAL_VALUE(0, falcon::tuple_apply<>(falcon::parameter_index<0,2,1>(), t, S3()));
	}
	{
		tuple3_type t(1,2,60);
		S3 f;
		CHECK_EQUAL_VALUE(30, falcon::tuple_apply<const S3&>(t, f));
	}
}

FALCON_TEST_TO_MAIN(tuple_apply_test)
