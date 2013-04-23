#include <iostream>
#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/ostream/join.hpp>
#include <falcon/iterator/counting_iterator.hpp>
#include "counting_iterator.hpp"

void counting_iterator_test()
{
	{
		typedef falcon::iterator::counting_iterator<int*> iterator;
		int a[] = {3,5,6,7,89,78,97,};
		iterator first(&a[0]);
		iterator last(4);
		{
			int cmp[] = {3,5,6,7};
			CHECK_SEQUENCE2(cmp, first, last);
		}
		first = falcon::iterator::make_counting_iterator<>(&a[0],2);
		first = falcon::iterator::make_counting_iterator<>(2,&a[0]);
	}
	{
		typedef falcon::iterator::counting_iterator<
			int*, falcon::iterator::count_and_iterator_comparison_tag
		> iterator;
		int a[] = {3,5,6,7,89,78,97,};
		iterator first = falcon::iterator::make_counting_iterator<>(
			&a[0], falcon::iterator::count_and_iterator_comparison_tag()
		);
		iterator last(&a[7], 40);
		CHECK_SEQUENCE2(a, first, last);
	}
}

FALCON_TEST_TO_MAIN(counting_iterator_test)
