#include <test/test.hpp>
#include <falcon/functional/parameter_adapter.hpp>
#include <falcon/functional/operators.hpp>
#include "parameter_adapter.hpp"

void parameter_adapter_test()
{
	typedef falcon::parameter_adapter<
		falcon::late_plus,
		falcon::range_parameter_index_tag<1, 2>
	> adapter_type;
	adapter_type adapter;
	CHECK_EQUAL_VALUE(6, adapter(1, 2, 4, 8));
	CHECK_EQUAL_VALUE(11, adapter(1, 7, 4, 8));
	CHECK_EQUAL_VALUE(12, adapter(1, 7, 5, 8));
}

FALCON_TEST_TO_MAIN(parameter_adapter_test)
