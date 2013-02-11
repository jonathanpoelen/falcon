#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/opposite_direction_iterator.hpp>
#include "opposite_direction_iterator.hpp"

void opposite_direction_iterator_test()
{
	typedef falcon::iterator::opposite_direction_iterator<int*> iterator;
	int a[]{0,1,2,3,4,5};
	int aa[] = {5,4,3,2,1,0};
	iterator first = iterator(std::end(a)-1);
	iterator last = falcon::iterator::make_opposite_direction_iterator<>(std::begin(a)-1);
	CHECK_SEQUENCE2(aa, first, last);
}

FALCON_TEST_TO_MAIN(opposite_direction_iterator_test)
