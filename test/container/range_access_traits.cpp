#include <test/test.hpp>
#include <vector>
#include <array>
#include <type_traits>
#include <falcon/container/range_access_traits.hpp>
#include "range_access_traits.hpp"

void range_access_traits_test()
{
	typedef std::array<int, 3> container1;
	typedef std::vector<int> container2;

	CHECK_NOTYPENAME_TYPE(container1::iterator,
						  falcon::range_access_iterator<container1>::type);
	CHECK_NOTYPENAME_TYPE(container2::iterator,
						  falcon::range_access_iterator<container2>::type);
	CHECK_NOTYPENAME_TYPE(container1::const_iterator,
						  falcon::range_access_iterator<const container1>::type);
	CHECK_NOTYPENAME_TYPE(container2::const_iterator,
						  falcon::range_access_iterator<const container2>::type);

	container1 a;
	CHECK(a.begin() == falcon::range_access_traits<container1>::begin(a));
	CHECK(a.cbegin() == falcon::range_access_traits<const container1>::begin(a));
}

FALCON_TEST_TO_MAIN(range_access_traits_test)
