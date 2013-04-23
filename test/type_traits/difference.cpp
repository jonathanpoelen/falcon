#include <test/test.hpp>
#include <vector>
#include <falcon/type_traits/difference.hpp>
#include "difference.hpp"

void difference_test()
{
	using falcon::difference;

	CHECK_TYPE(int, difference<int>);
	CHECK_TYPE(float, difference<float>);
	CHECK_TYPE(std::ptrdiff_t, difference<int*>);
	CHECK_TYPE(std::ptrdiff_t, difference<const int*>);
	CHECK_TYPE(std::ptrdiff_t, difference<const int* const>);
	CHECK_TYPE(std::ptrdiff_t, difference<const int* const*>);
	CHECK_TYPE(int, difference<volatile int>);

	typedef typename std::vector<int>::iterator iterator;
	CHECK_TYPE(typename iterator::difference_type, difference<iterator>);

}

FALCON_TEST_TO_MAIN(difference_test)
