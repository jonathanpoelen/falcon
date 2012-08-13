#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/recursive_iterator.hpp>
#include "recursive_iterator.hpp"

void recursive_iterator_test()
{
	typedef std::vector<int> subttype;
	typedef std::vector<subttype> container_type;

	subttype sub1 = {3,4};
	subttype sub2 = {7,8};
	container_type v(3, subttype(2,1));
	v[1] = sub1;
	v[2] = sub2;

	auto it = falcon::iterator::recursive_iterator<>(v);
	auto end = v.end();

	CHECK_EQUAL_VALUE(1, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(1, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(3, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(4, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(7, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(8, *it);
	CHECK_EQUAL_VALUE(false, ++it != end);
}
FALCON_TEST_TO_MAIN(recursive_iterator_test)
