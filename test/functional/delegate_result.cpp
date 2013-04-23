#include <test/test.hpp>
#include <falcon/functional/delegate_result.hpp>
#include "delegate_result.hpp"

void delegate_result_test()
{
	{
		struct S{
			int operator()(){ return 3; }
			int operator()(int n){ return n; }
		};

		struct SS{ int operator()(int n){ return n*2; } };

		CHECK_EQUAL_VALUE(falcon::delegate(SS(),S())(), 6);
		CHECK_EQUAL_VALUE(falcon::delegate(SS(),S())(7), 14);
	}
	{
		struct S{
			typedef int argument_type;
			int operator()(int){ return 3; }
		};

		struct SS{
			typedef int result_type;
			int operator()(int n){ return n*2; }
		};

		CHECK_EQUAL_VALUE(falcon::delegate1(SS(),S())(1), 6);
		falcon::delegate_result<SS,S>() = falcon::delegate1(SS(),S());
	}
	{
		struct S{
			typedef int first_argument_type;
			typedef int second_argument_type;
			int operator()(int,int){ return 3; }
		};

		struct SS{
			typedef int result_type;
			int operator()(int n){ return n*2; }
		};

		CHECK_EQUAL_VALUE(falcon::delegate2(SS(),S())(1,1), 6);
		falcon::delegate_result<SS,S>() = falcon::delegate2(SS(),S());
	}
}

FALCON_TEST_TO_MAIN(delegate_result_test)
