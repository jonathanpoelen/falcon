#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/bit_iterator.hpp>
#include "bit_iterator.hpp"

void bit_iterator_test()
{
	typedef std::vector<unsigned char> container_type;
	typedef typename container_type::iterator iterator;
	container_type v = {0xff, 0x0f, 0xf0, 0x80};

	falcon::iterator::bit_iterator<iterator> it(v.begin(), 0);
	falcon::iterator::bit_iterator<iterator> end(v.end(), 0);

	for (int i = 0; i < 8 + 4; ++i, ++it)
	{
		CHECK_EQUAL_VALUE(true, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	for (int i = 0; i < 8; ++i, ++it)
	{
		CHECK_EQUAL_VALUE(false, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	for (int i = 0; i < 4; ++i, ++it)
	{
		CHECK_EQUAL_VALUE(true, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	for (int i = 0; i < 7; ++i, ++it)
	{
		CHECK_EQUAL_VALUE(false, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	CHECK_EQUAL_VALUE(true, *it);
	CHECK_EQUAL_VALUE(true, end == ++it);

	CHECK_EQUAL_VALUE(true, end != --it);
	end = falcon::iterator::bit_iterator<iterator>(v.begin() - 1, 7);
	CHECK_EQUAL_VALUE(true, *it);
	*it = false;
	CHECK_EQUAL_VALUE(false, *it);
	--it;
	for (int i = 0; i < 7; ++i, --it)
	{
		CHECK_EQUAL_VALUE(false, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	for (int i = 0; i < 4; ++i, --it)
	{
		CHECK_EQUAL_VALUE(true, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	for (int i = 0; i < 8; ++i, --it)
	{
		CHECK_EQUAL_VALUE(false, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	for (int i = 0; i < 8 + 4; ++i, --it)
	{
		CHECK_EQUAL_VALUE(true, *it);
		CHECK_EQUAL_VALUE(true, end != it);
	}
	CHECK_EQUAL_VALUE(true, end == it);
}
FALCON_TEST_TO_MAIN(bit_iterator_test)