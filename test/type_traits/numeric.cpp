#include <test/test.hpp>
#include <falcon/type_traits/numeric.hpp>
#include <boost/static_assert.hpp>
#include "numeric.hpp"

#define _NUMERIC_TEST(name, _Choose, _N) STATIC_ASSERT(sizeof(typename falcon::minimal_##name<_Choose>::type) == _N)

void numeric_test()
{
#define NUMERIC_TEST(_Choose, _N) _NUMERIC_TEST(bits, _Choose, _N)
	NUMERIC_TEST(1,1);
	NUMERIC_TEST(8,1);
	NUMERIC_TEST(10,2);
	NUMERIC_TEST(16,2);
	NUMERIC_TEST(50,8);
#undef NUMERIC_TEST

#define NUMERIC_TEST(_Choose, _N) _NUMERIC_TEST(int, _Choose, _N)
	NUMERIC_TEST(1,1);
	NUMERIC_TEST(100,1);
	NUMERIC_TEST(255,1);
	NUMERIC_TEST(1024,2);
	NUMERIC_TEST(65535,2);
#undef NUMERIC_TEST
}

#undef _NUMERIC_TEST
FALCON_TEST_TO_MAIN(numeric_test)
