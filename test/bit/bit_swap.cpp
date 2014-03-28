#include <test/test.hpp>
#include <falcon/bit/bit_swap.hpp>
#include "bit_swap.hpp"

void bit_swap_test()
{
	{
		uint16_t i = 0x0005;
		CHECK_EQUAL_VALUE(0x0005, i);
		falcon::bit_swap(i);
		CHECK_EQUAL_VALUE(0xA000, i);
		falcon::bit_swap(i);
		CHECK_EQUAL_VALUE(0x0005, i);
	}
	{
		int16_t ii = 5;
		uint16_t& i = *reinterpret_cast<uint16_t*>(&ii);
		CHECK_EQUAL_VALUE(0x0005, i);
		falcon::detail::bit::bit16_swap(i);
		CHECK_EQUAL_VALUE(static_cast<uint16_t>(0xA000), i);
		falcon::detail::bit::bit16_swap(i);
		CHECK_EQUAL_VALUE(0x0005, i);
	}
	{
		uint16_t i[] = {0x0001,0x0001};
		CHECK_EQUAL_VALUE(0x0001, i[0]);
		CHECK_EQUAL_VALUE(0x0001, i[1]);
		falcon::bit_swap(i);
		CHECK_EQUAL_VALUE(0x8000, i[0]);
		CHECK_EQUAL_VALUE(0x8000, i[1]);
		falcon::bit_swap(i);
		CHECK_EQUAL_VALUE(0x0001, i[0]);
		CHECK_EQUAL_VALUE(0x0001, i[1]);
	}
	{
		struct Test
		{
			uint32_t l;
			uint32_t l2;
		};
		Test i = {0x00000001,0x00000001};
		CHECK_EQUAL_VALUE(0x00000001u, i.l);
		CHECK_EQUAL_VALUE(0x00000001u, i.l2);
		falcon::bit_swap(i);
		CHECK_EQUAL_VALUE(0x80000000, i.l);
		CHECK_EQUAL_VALUE(0x80000000, i.l2);
		falcon::bit_swap(i);
		CHECK_EQUAL_VALUE(0x00000001u, i.l);
		CHECK_EQUAL_VALUE(0x00000001u, i.l2);
	}
}
FALCON_TEST_TO_MAIN(bit_swap_test)
