#include <test/test.hpp>
#include <falcon/functional/special_call.hpp>
#include <falcon/functional/call_partial_recursive_param_loop.hpp>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/operators.hpp>
#include "call.hpp"

void call_test() {
	CHECK_EQUAL_VALUE(12, falcon::call_last_param<2>(falcon::late_plus(), 1, 2, 4, 8));
	CHECK_EQUAL_VALUE(3, falcon::call_first_param<2>(falcon::late_plus(), 1, 2, 4, 8));
	CHECK_EQUAL_VALUE(9, falcon::call_ignore_param<1, 2>(falcon::late_plus(), 1, 2, 4, 8));

	CHECK_EQUAL_VALUE(12, falcon::call_partial_param_loop<2>(falcon::late_plus(), 1, 2, 4, 8));
	CHECK_EQUAL_VALUE(15, falcon::call_partial_recursive_param_loop<2>(falcon::late_plus(), 1, 2, 4, 8));
	CHECK_EQUAL_VALUE(25, falcon::call_partial_recursive_param_loop<2>(falcon::late_plus(), 1, 2, 4, 8, 10));
	CHECK_EQUAL_VALUE(5, falcon::call_partial_recursive_param_loop<2>(falcon::late_plus(), 1, 4));

	CHECK_EQUAL_VALUE(6, falcon::call_range_param<1, 2>(falcon::late_plus(), 1, 2, 4, 8));

	CHECK_EQUAL_VALUE(-2, falcon::call_reverse_param<0, 2>(falcon::late_minus(), 4, 2));
}

FALCON_TEST_TO_MAIN(call_test)
