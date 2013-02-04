#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/iterator_iterator.hpp>
#include "iterator_iterator.hpp"

void iterator_iterator_test()
{
	int a[2] = {1,2}, b[3] = {3,4,5};
	{
		falcon::iterator::iterator_iterator<int *> first({
			{std::begin(a), std::end(a)},
			{std::begin(b), std::end(b)}
		});
		falcon::iterator::iterator_iterator<int *> last({{std::end(b), 0}});
		falcon::iterator::iterator_iterator<int *> last2(std::end(b));
		CHECK(last == last2);
		{
			int aa[] = {1,2,3,4,5};
			CHECK_SEQUENCE2(aa, first, last);
		}
	}
	falcon::iterator::iterator_iterator<int *> first({
		{std::begin(a), std::end(a)},
		{std::begin(b), std::end(b)}
	});
	int i = 1;
	while (first.valid() && i != 6){
		CHECK_EQUAL_VALUE(i++, *first);
		++first;
	}
	CHECK_EQUAL_VALUE(i, 6);
	CHECK(!first.valid());
}

FALCON_TEST_TO_MAIN(iterator_iterator_test)
