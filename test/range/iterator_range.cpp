#include <sstream>
#include <algorithm>
#include <test/test.hpp>
#include <falcon/range/iterator_range.hpp>
#include "iterator_range.hpp"

void iterator_range_test()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	falcon::iterator_range<int*> cont(&a[2], &a[9]);
	std::ostringstream ss;
	std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
	CHECK_EQUAL_VALUE(ss.str(), "2,3,4,5,6,7,8,");
}

FALCON_TEST_TO_MAIN(iterator_range_test)
