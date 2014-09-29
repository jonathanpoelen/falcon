#include <sstream>
#include <iomanip>
#include <falcon/flag.hpp>
#include "test.hpp"
#include "flag.hpp"

void flag_test()
{
	CHECK_TYPE(falcon::flag0, falcon::flag_selector<0>);
	CHECK_TYPE(falcon::flag32, falcon::flag_selector<1>);
	CHECK_TYPE(falcon::flag32, falcon::flag_selector<10>);
	CHECK_TYPE(falcon::flag32, falcon::flag_selector<32>);
	CHECK_TYPE(falcon::flag64, falcon::flag_selector<33>);
	CHECK_TYPE(falcon::flag64, falcon::flag_selector<50>);
	CHECK_TYPE(falcon::flag64, falcon::flag_selector<64>);
	CHECK_TYPE(falcon::flag128, falcon::flag_selector<65>);
	CHECK_TYPE(falcon::flag128, falcon::flag_selector<100>);
	CHECK_TYPE(falcon::flag128, falcon::flag_selector<128>);
	CHECK_TYPE(falcon::flag192, falcon::flag_selector<129>);

	{
		std::ostringstream ss;
		{
			falcon::flag0 flag;
			ss << flag << bool(flag & flag) << bool(flag | flag);
			flag += 0;
			{
				unsigned i = 415;
				flag += i;
			}
			{
				std::size_t i = 415;
				flag -= i;
			}
			CHECK_EQUAL_VALUE(ss.str(), "00");
		}
	}
	{
		falcon::flag32 flag(0xff);
		flag += 0xff00;
		flag -= 0x0001L;
		CHECK_EQUAL_VALUE(flag.get(), 0xfffeu);
		flag <<= 4;
		CHECK_EQUAL_VALUE(flag.get(), 0xfffe0u);
	}
	{
		falcon::flag128 flag = falcon::flag128::full();

		CHECK_EQUAL_VALUE(true, flag.has(0));
		CHECK_EQUAL_VALUE(true, flag.has(4));
		CHECK_EQUAL_VALUE(flag, flag);
		CHECK_EQUAL_VALUE(falcon::flag128(), ~flag);

		flag <<= 4;
		CHECK_EQUAL_VALUE(falcon::flag64::full(), flag[0]);
		CHECK_EQUAL_VALUE(falcon::flag64::full() << 4, flag[1]);

		flag <<= 100;
		CHECK_EQUAL_VALUE(falcon::flag64::full() << 40, falcon::flag64(flag[0]));
		CHECK_EQUAL_VALUE(0u, flag[1]);

		flag = falcon::flag128::full();

		flag >>= 4;
		CHECK_EQUAL_VALUE(falcon::flag64::full() >> 4, falcon::flag64(flag[0]));
		CHECK_EQUAL_VALUE(falcon::flag64::full(), falcon::flag64(flag[1]));

		flag >>= 100;
		CHECK_EQUAL_VALUE(falcon::flag64(flag[0]), 0u);
		///BUG god for gcc-4.7, fail with gcc-4.6…
		CHECK_EQUAL_VALUE(falcon::flag64::full() >> 40, falcon::flag64(flag[1]));
	}
	{
		falcon::flag256 flag = falcon::flag256::full();

		CHECK_EQUAL_VALUE(true, flag.has(0));
		CHECK_EQUAL_VALUE(true, flag.has(4));
		CHECK_EQUAL_VALUE(flag, flag);
		CHECK_EQUAL_VALUE(falcon::flag256(), ~flag);

		flag <<= 4;
		CHECK_EQUAL_VALUE(falcon::flag64::full(), flag[0]);
		CHECK_EQUAL_VALUE(falcon::flag64::full(), flag[1]);
		CHECK_EQUAL_VALUE(falcon::flag64::full(), flag[2]);
		CHECK_EQUAL_VALUE(falcon::flag64::full() << 4, flag[3]);

		flag <<= 200;
		CHECK_EQUAL_VALUE(falcon::flag64::full() << (204%64), falcon::flag64(flag[0]));
		CHECK_EQUAL_VALUE(0u, flag[1]);
		CHECK_EQUAL_VALUE(0u, flag[2]);
		CHECK_EQUAL_VALUE(0u, flag[3]);

		flag = falcon::flag256::full();

		flag >>= 4;
		CHECK_EQUAL_VALUE(falcon::flag64::full() >> 4, falcon::flag64(flag[0]));
		CHECK_EQUAL_VALUE(falcon::flag64::full(), falcon::flag64(flag[1]));
		CHECK_EQUAL_VALUE(falcon::flag64::full(), falcon::flag64(flag[2]));
		CHECK_EQUAL_VALUE(falcon::flag64::full(), falcon::flag64(flag[3]));

		flag >>= 64*3+8;
		CHECK_EQUAL_VALUE(falcon::flag64(flag[0]), 0u);
		CHECK_EQUAL_VALUE(falcon::flag64(flag[1]), 0u);
		CHECK_EQUAL_VALUE(falcon::flag64(flag[2]), 0u);
		CHECK_EQUAL_VALUE(falcon::flag64::full() >> (204%64), falcon::flag64(flag[3]));
	}

	{
		std::ostringstream ss;
		falcon::flag32 flag(0xf00f1144);
		ss << flag << '\n'
		<< std::setw(40) << std::setfill('0') << flag << '\n'
		<< std::setw(40) << std::left << flag;
		CHECK_EQUAL_VALUE(ss.str(),
						  "11110000000011110001000101000100\n"
						 "0000000011110000000011110001000101000100\n"
						 "1111000000001111000100010100010000000000");
	}
}
FALCON_GROUP_TEST_TO_MAIN(flag_test)
