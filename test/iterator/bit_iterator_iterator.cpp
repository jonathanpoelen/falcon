#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/bit_iterator_iterator.hpp>
#include "bit_iterator_iterator.hpp"

void bit_iterator_iterator_test()
{
	typedef std::vector<unsigned char> container_type;
	typedef typename container_type::iterator iterator;
	container_type v = {0xff, 0xf0, 0x0f, 0x01};

	{
		falcon::iterator::bit_iterator_iterator<iterator> it(v.begin(), 0x80);
		falcon::iterator::bit_iterator_iterator<iterator> end(v.end(), 0x80);

		for (int i = 0; i < 8; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0x80 >> i, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8/2; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0x80 >> i, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8/2; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0x08 >> i, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8-1; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		CHECK_EQUAL_VALUE(0x01, *it);
		CHECK_EQUAL_VALUE(true, end == ++it);
	}

	{
		falcon::iterator::reverse_bit_iterator_iterator<iterator> it(v.begin(), 1);
		falcon::iterator::reverse_bit_iterator_iterator<iterator> end(v.end(), 1);

		for (int i = 0; i < 8; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(1 << i, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8/2; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8/2; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0x10 << i, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8/2; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(1 << i, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		for (int i = 0; i < 8/2; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		CHECK_EQUAL_VALUE(1, *it);
		CHECK_EQUAL_VALUE(true, end != it);
		++it;
		for (int i = 0; i < 8-1; ++i, ++it)
		{
			CHECK_EQUAL_VALUE(0, *it);
			CHECK_EQUAL_VALUE(true, end != it);
		}
		CHECK_EQUAL_VALUE(true, end == it);
	}
}
FALCON_TEST_TO_MAIN(bit_iterator_iterator_test)
