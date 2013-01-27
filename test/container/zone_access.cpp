#include <test/test.hpp>
#include <sstream>
#include <falcon/container/zone_access.hpp>
#include <falcon/container/container_wrapper.hpp>
#include "zone_access.hpp"

void zone_access_test()
{
	int a[]{
		0, 1, 2, 3, 4,
		5, 6, 7, 8, 9,
		10,11,12,13,14,
		15,16,17,18,19,
		20,21,22,23,24
	};

	typedef decltype(a) container_type;
	typedef falcon::zone_access<container_type> zone_access;
	typedef falcon::container_wrapper<container_type, zone_access> zone_type;
	zone_type cont(a, {5, 1, 1, 3, 3});
	{
		zone_access zone{5, 1, 1, 3, 3};
		CHECK(cont.begin() == zone.begin(a));
		CHECK(cont.end() == zone.end(a));
	}
	std::ostringstream ss;
	std::copy<>(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
	CHECK_EQUAL_VALUE(ss.str(), "6,7,8,11,12,13,16,17,18,");
	zone_type::iterator first = cont.begin();
	CHECK_EQUAL_VALUE(6, *first);
	first += 2;
	CHECK_EQUAL_VALUE(8, *first);
	first += 2;
	CHECK_EQUAL_VALUE(12, *first);
	first += 2;
	CHECK_EQUAL_VALUE(16, *first);
	first += 2;
	CHECK_EQUAL_VALUE(18, *first);
	first += 2;
	CHECK(first > cont.end());
}

FALCON_TEST_TO_MAIN(zone_access_test)
