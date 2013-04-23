#include <test/test.hpp>
#include <array>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/functional/store_if.hpp>
#include <falcon/utility/maker.hpp>
#include "store_if.hpp"

void store_if_test()
{
	typedef std::array<int, 6> container_type;
	typedef typename container_type::iterator iterator;

	falcon::store_if<int> store;
	container_type c CPP0X(CPP0X(1,2,3,0,4,5));

	for (iterator it = c.begin(), end = c.end();
		 it != end && store(*it); ++it)
		;

	CHECK(store.get());
	CHECK_EQUAL_VALUE(3, *store.get());

	//store.set(nullptr);
	store.clear();
	c[3] = -1;
	for (iterator it = c.begin(), end = c.end();
		 it != end && store(*it); ++it)
		 ;

	CHECK(store.get());
	CHECK_EQUAL_VALUE(5, *store.get());

}
FALCON_TEST_TO_MAIN(store_if_test)
