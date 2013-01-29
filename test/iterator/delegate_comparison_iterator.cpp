#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/delegate_comparison_iterator.hpp>
#include "delegate_comparison_iterator.hpp"

void delegate_comparison_iterator_test()
{
	const char * cstr = "plop-plop";
	const char * cstr2 = "PLOP";

	falcon::iterator::delegate_comparison_iterator<const char *, const char *> it(cstr, cstr2);
	falcon::iterator::delegate_comparison_iterator<const char *, const char *> end(cstr2+4);

	{
		char a[] = {'p', 'l', 'o', 'p'};
		CHECK_SEQUENCE2(a, it, end);
	}
}
FALCON_TEST_TO_MAIN(delegate_comparison_iterator_test)
