#include <test/test.hpp>
#include <falcon/type_traits/reference_selector.hpp>
#include <falcon/c++/reference.hpp>
#include "reference_selector.hpp"

void reference_selector_test()
{
	using falcon::match_reference_selector;

#if __cplusplus >= 201103L
	CHECK_TYPE(float&&, match_reference_selector<int&&, float>);
#endif
	CHECK_TYPE(int&, match_reference_selector<const int, int&>);
	CHECK_TYPE(volatile float&, match_reference_selector<int&, volatile float>);
	CHECK_TYPE(float(&)[4], match_reference_selector<int&, float[4]>);

}

FALCON_TEST_TO_MAIN(reference_selector_test)
