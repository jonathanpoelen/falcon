#include <test/test.hpp>
#include <falcon/iterator/delegate_comparison_iterator.hpp>
#include "delegate_comparison_iterator.hpp"

void delegate_comparison_iterator_test()
{
	const char * cstr = "plop-plop";
	const char * cstr2 = "PLOP";

	falcon::iterator::delegate_comparison_iterator<const char *, const char *> it(cstr, cstr2);
	falcon::iterator::delegate_comparison_iterator<const char *, const char *> end(cstr2+4);

	CHECK_EQUAL_VALUE('p', *it);
	CHECK_EQUAL_VALUE(true, end != ++it);
	CHECK_EQUAL_VALUE('l', *it);
	CHECK_EQUAL_VALUE(true, end != ++it);
	CHECK_EQUAL_VALUE('o', *it);
	CHECK_EQUAL_VALUE(true, end != ++it);
	CHECK_EQUAL_VALUE('p', *it);
	CHECK_EQUAL_VALUE(true, end == ++it);
}
FALCON_TEST_TO_MAIN(delegate_comparison_iterator_test)
