#include <falcon/literal/chrono.hpp>
#include "test.hpp"

void literal_test()
{
	using namespace falcon::literal::chrono;
	if (std::chrono::nanoseconds(5) != 5_nanoseconds)
		CHECK(0);
}

FALCON_GROUP_TEST_TO_MAIN(literal_test)
