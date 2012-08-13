#include <test/test.hpp>
#include <falcon/iterator/pseudo_iterator.hpp>
#include "pseudo_iterator.hpp"

void pseudo_iterator_test()
{
	falcon::iterator::pseudo_iterator<int> it(2);
	falcon::iterator::pseudo_iterator<int> end(5);

	CHECK_EQUAL_VALUE(2, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(2, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(2, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	*it = 3;
	CHECK_EQUAL_VALUE(3, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(3, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
}
FALCON_TEST_TO_MAIN(pseudo_iterator_test)
