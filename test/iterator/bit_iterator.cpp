#include <test/test.hpp>
#include <falcon/iterator/bit_iterator.hpp>
#include "bit_iterator.hpp"

void bit_iterator_test()
{
	{
		typedef falcon::iterator::bit_iterator<unsigned char> iterator_type;
		iterator_type it(1<<7/*iterator_type::first_value*/);
		iterator_type end;

		CHECK_EQUAL_VALUE(0, *end);
		CHECK(it != end);
		CHECK_EQUAL_VALUE(1<<7, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<6, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<5, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<4, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<3, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<2, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<1, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1, *it);
		CHECK(++it == end);
		CHECK_EQUAL_VALUE(0, *it);
	}

	{
		typedef falcon::iterator::reverse_bit_iterator<unsigned char> iterator_type;
		iterator_type it(1);
		iterator_type end(1u<<8);

		//CHECK_EQUAL_VALUE(0, *end);
		CHECK(it != end);
		CHECK_EQUAL_VALUE(1, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<1, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<2, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<3, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<4, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<5, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<6, *it);
		CHECK(++it != end);
		CHECK_EQUAL_VALUE(1<<7, *it);
		CHECK(++it == end);
		//CHECK_EQUAL_VALUE(0, *it);
	}
}
FALCON_TEST_TO_MAIN(bit_iterator_test)
