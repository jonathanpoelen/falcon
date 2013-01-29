#include <vector>
#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include "nexter_iterator.hpp"

void nexter_iterator_test()
{
	typedef std::vector<int> container_type;
	typedef typename container_type::iterator iterator;
	std::vector<int> c = {0,1,2,3,4};

	auto it = falcon::iterator::make_nexter_iterator<>(c.begin(),
																										 [](iterator&__it){return ++__it;}
	);
	auto end = falcon::iterator::make_nexter_iterator<>(c.end(), it.nexter());

	{
		int a[] = {0,1,2,3,4,};
		CHECK_SEQUENCE_M2(a, it, end, ++*it);
	}
	it = c.begin();
	{
		int a[] = {1,2,3,4,5};
		CHECK_SEQUENCE_M2(a, it, end, ++*it);
	}
}
FALCON_TEST_TO_MAIN(nexter_iterator_test)
