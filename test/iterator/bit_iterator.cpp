#include <vector>
#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/bit_iterator.hpp>
#include "bit_iterator.hpp"

void bit_iterator_test()
{
	typedef std::vector<unsigned char> container_type;
	typedef typename container_type::iterator iterator;
	container_type v = {0xff, 0x0f, 0xf0, 0x80};

	falcon::iterator::bit_iterator<iterator> it(v.begin(), 0);
	falcon::iterator::bit_iterator<iterator> end(v.end(), 0);

	{
		bool ba[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1};
		CHECK_SEQUENCE2(ba, it, end);
	}
	CHECK_EQUAL_VALUE(true, end != --it);
	end = falcon::iterator::bit_iterator<iterator>(v.begin() - 1, 7);
	CHECK_EQUAL_VALUE(true, *it);
	*it = false;
	{
		bool ba[] = {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1};
		CHECK_REVERSE_SEQUENCE2(ba, it, end);
	}
}
FALCON_TEST_TO_MAIN(bit_iterator_test)