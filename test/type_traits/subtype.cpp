#include <test/test.hpp>
#include <falcon/type_traits/subtype.hpp>
#include <vector>
#include "subtype.hpp"

void subtype_test()
{
	using falcon::subtype;

	CHECK_TYPE(long&, subtype<long*>);
	CHECK_TYPE(char&, subtype<char[5]>);
	CHECK_TYPE(float&, subtype<typename std::vector<float>::iterator>);
}
FALCON_TEST_TO_MAIN(subtype_test)
