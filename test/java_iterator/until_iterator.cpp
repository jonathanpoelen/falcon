#include <test/test.hpp>
#include <falcon/java_iterator/until_iterator.hpp>
#include "until_iterator.hpp"

void until_iterator_test()
{
	const char * cstr = "plop\n";

	auto it = falcon::java_iterator::make_until_iterator<>(&cstr[0], '\n');
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE('p', it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE('l', it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE('o', it.next());
	CHECK_EQUAL_VALUE(true, it.valid());
	CHECK_EQUAL_VALUE('p', it.next());
	CHECK_EQUAL_VALUE(false, it.valid());
}


FALCON_TEST_TO_MAIN(until_iterator_test)
