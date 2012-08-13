#include <test/test.hpp>
#include <falcon/bit/circular_bit.hpp>
#include "circular_bit.hpp"

void circular_bit_test()
{
	{
		falcon::circular_bit<uint8_t> circular;

		CHECK_EQUAL_VALUE(0x80,*circular);
		CHECK_EQUAL_VALUE(0x40,*++circular);
		CHECK_EQUAL_VALUE(0x20,*++circular);
		CHECK_EQUAL_VALUE(0x10,*++circular);
		CHECK_EQUAL_VALUE(0x08,*++circular);
		CHECK_EQUAL_VALUE(0x04,*++circular);
		CHECK_EQUAL_VALUE(0x02,*++circular);
		CHECK_EQUAL_VALUE(0x01,*++circular);
		CHECK_EQUAL_VALUE(0x80,*++circular);
		CHECK_EQUAL_VALUE(0x40,*++circular);
	}
	{
		falcon::reverse_circular_bit<uint8_t> circular;

		CHECK_EQUAL_VALUE(0x01,*circular);
		CHECK_EQUAL_VALUE(0x02,*++circular);
		CHECK_EQUAL_VALUE(0x04,*++circular);
		CHECK_EQUAL_VALUE(0x08,*++circular);
		CHECK_EQUAL_VALUE(0x10,*++circular);
		CHECK_EQUAL_VALUE(0x20,*++circular);
		CHECK_EQUAL_VALUE(0x40,*++circular);
		CHECK_EQUAL_VALUE(0x80,*++circular);
		CHECK_EQUAL_VALUE(0x01,*++circular);
		CHECK_EQUAL_VALUE(0x02,*++circular);
	}
}
FALCON_TEST_TO_MAIN(circular_bit_test)
