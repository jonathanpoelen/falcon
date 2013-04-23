#include <test/test.hpp>
#include <vector>
#include <falcon/range/range.hpp>
#include <falcon/range/range_modifier.hpp>
#include "range.hpp"

void range_test()
{
	typedef std::vector<int> container_type;

	container_type v({1,2,3,4});

	falcon::make_range_modifier(v) += 2;
	falcon::make_range(v.begin(), v.begin()+2).modifier() += 2;
	falcon::range_iterator(v).modifier() += 2;

	CHECK_EQUAL_VALUE(7, v[0]);
	CHECK_EQUAL_VALUE(8, v[1]);
	CHECK_EQUAL_VALUE(7, v[2]);
	CHECK_EQUAL_VALUE(8, v[3]);
}

FALCON_TEST_TO_MAIN(range_test)
