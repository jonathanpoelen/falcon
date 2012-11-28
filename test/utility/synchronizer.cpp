#include <test/test.hpp>
#include <falcon/utility/synchronizer.hpp>
#include <falcon/tuple/ostream.hpp>
#include "synchronizer.hpp"

using namespace falcon::tuple::ostream;
void synchronizer_test()
{
	{
		int i = 2, i2 = 4;
		falcon::synchronizer<int&, int&> synchronizer(i, i2);
		++synchronizer;
		CHECK_EQUAL_VALUE(i, 3);
		CHECK_EQUAL_VALUE(i2, 5);
		++falcon::synchronize(i, i2);
		CHECK_EQUAL_VALUE(i, 4);
		CHECK_EQUAL_VALUE(i2, 6);
		auto t = std::tie(i,i2);
		++falcon::tuple_synchronise(t);
		CHECK_EQUAL_VALUE(i, 5);
		CHECK_EQUAL_VALUE(i2, 7);
	}

	{
		const char * s = "plop";
		auto sync = falcon::make_synchronizer<>(s, s+1);
		CHECK_EQUAL_VALUE(sync[0],		std::make_tuple('p', 'l'));
		CHECK_EQUAL_VALUE(*sync,		std::make_tuple('p', 'l'));
		CHECK_EQUAL_VALUE((sync+=1)[0],	std::make_tuple('l', 'o'));
		CHECK_EQUAL_VALUE(sync + 1,		std::make_tuple(s+2, s+3));
	}

	{
		std::string str = "plop";
		std::string str2 = "pop";
		auto  sync = falcon::make_synchronizer<>(str, str2);
		CHECK_EQUAL_VALUE((sync->*&std::string::size)(), std::make_tuple(4,3));
	}
}

FALCON_TEST_TO_MAIN(synchronizer_test)
