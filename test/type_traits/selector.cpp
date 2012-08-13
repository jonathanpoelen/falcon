#include <test/test.hpp>
#include <falcon/type_traits/selector.hpp>
#include "selector.hpp"

void selector_test()
{
	using falcon::match_selector;
	using falcon::cv_selector;
	using falcon::reference_qualified;
	namespace reference_type = falcon::reference_type;

	CHECK_TYPE(const volatile int, cv_selector<int, true, true>);

	CHECK_TYPE(const volatile float, match_selector<const volatile int, float>);
	CHECK_TYPE(const int, match_selector<const int, int>);
	CHECK_TYPE(volatile float, match_selector<volatile int, float>);
	CHECK_TYPE(float&, match_selector<volatile int&, float>);
	CHECK_TYPE(const float[4], match_selector<const int, float[4]>);
	CHECK_TYPE(float(&)[4], match_selector<const int&, float[4]>);

	STATIC_CHECK_VALUE(reference_type::lvalue_reference, reference_qualified<volatile int&>);

}

FALCON_TEST_TO_MAIN(selector_test)
