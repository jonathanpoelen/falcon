#include <test/test.hpp>
#include <vector>
#include <falcon/type_traits/dimension.hpp>
#include "dimension.hpp"

void dimension_test()
{
	using falcon::dimension;

	STATIC_CHECK_VALUE(0, dimension<int>);
	STATIC_CHECK_VALUE(0, dimension<float>);
	STATIC_CHECK_VALUE(1, dimension<int[5]>);
	STATIC_CHECK_VALUE(1, dimension<const volatile int[5]>);
	STATIC_CHECK_VALUE(1, dimension<const int[5]>);
	typedef const int v_type;
	typedef v_type arr_type[1];
	STATIC_CHECK_VALUE(2, dimension<const arr_type [5]>);

	typedef std::vector<int> container;
	STATIC_CHECK_VALUE(1, dimension<container>);

	typedef std::vector<container> container2;
	STATIC_CHECK_VALUE(2, dimension<container2>);

}

FALCON_TEST_TO_MAIN(dimension_test)
