#include <test/test.hpp>
#include <vector>
#include <falcon/container/container_wrapper.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/algorithm/algorithm.hpp>
#include "container_wrapper.hpp"

void container_wrapper_test()
{
	typedef std::vector<int> array_type;
	array_type arr( {4,4,2,1});
	falcon::container_wrapper<array_type> wrap(arr);
	CHECK_EQUAL_VALUE(4, (*wrap.begin())++);
	CHECK_EQUAL_VALUE(5, *wrap.begin());

	falcon::sort(wrap);
	CHECK_EQUAL_VALUE(1, *wrap.begin());
	CHECK_EQUAL_VALUE(2, *(wrap.begin()+1));
	CHECK_EQUAL_VALUE(4, *(wrap.begin()+2));
	CHECK_EQUAL_VALUE(5, *(wrap.begin()+3));

	falcon::sort(falcon::container_wrapper<array_type, falcon::reverse_range_access_traits<array_type>>(arr));
	CHECK_EQUAL_VALUE(5, *wrap.begin());
	CHECK_EQUAL_VALUE(4, *(wrap.begin()+1));
	CHECK_EQUAL_VALUE(2, *(wrap.begin()+2));
	CHECK_EQUAL_VALUE(1, *(wrap.begin()+3));
}

FALCON_TEST_TO_MAIN(container_wrapper_test)
