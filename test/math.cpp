#include <test/test.hpp>
#include <falcon/math.hpp>
#include "math.hpp"

void math_test()
{
	STATIC_ASSERT(3 == falcon::abs_diff<>(4,1));
	STATIC_ASSERT(3 == falcon::abs_diff<>(1,4));
	STATIC_ASSERT(5 == falcon::abs_diff<>(-4,1));
	STATIC_ASSERT(5 == falcon::abs_diff<>(1,-4));
	STATIC_ASSERT(3 == falcon::abs_diff<>(-4,-1));
	STATIC_ASSERT(3 == falcon::abs_diff<>(-1,-4));
	STATIC_ASSERT(5 == falcon::abs_diff<>(4,-1));
	STATIC_ASSERT(5 == falcon::abs_diff<>(-1,4));

	STATIC_ASSERT(4 == falcon::max<>(1,2,3,4));
	STATIC_ASSERT(1 == falcon::min<>(1,2,3,4));

	STATIC_ASSERT(32 == falcon::middle<>(10,55));
}
FALCON_GROUP_TEST_TO_MAIN(math_test)
