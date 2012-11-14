#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/indirect_iterator.hpp>
#include "indirect_iterator.hpp"

void indirect_iterator_test()
{
	int a = 0, b = 1, c = 2, d = 3, e = 4;
	typedef std::vector<int*> container_type;
	typedef typename container_type::iterator iterator;
	container_type cont = {&a,&b,&c,&d,&e};

	falcon::iterator::indirect_iterator<iterator> it(cont.begin());
	falcon::iterator::indirect_iterator<iterator> end(cont.end());

	CHECK_EQUAL_VALUE(true, it != end);
	CHECK_EQUAL_VALUE(0, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(1, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(2, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(3, (*it)++);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(4, (*it)++);
	CHECK_EQUAL_VALUE(false, ++it != end);
	it = cont.begin();
	CHECK_EQUAL_VALUE(true, it != end);
	CHECK_EQUAL_VALUE(1, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(2, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(3, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(4, *it);
	CHECK_EQUAL_VALUE(true, ++it != end);
	CHECK_EQUAL_VALUE(5, *it);
	CHECK_EQUAL_VALUE(false, ++it != end);
}
FALCON_TEST_TO_MAIN(indirect_iterator_test)