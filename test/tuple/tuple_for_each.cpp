#include <tuple>
#include <test/test.hpp>
#include <falcon/tuple/tuple_for_each.hpp>
#include <falcon/iostreams/put.hpp>
#include "tuple_for_each.hpp"

void tuple_for_each_test()
{
	std::ostringstream os;
	falcon::tuple_for_each(std::make_tuple(5, ' ', 55),
                         falcon::make_ostream_function(os));
	CHECK_EQUAL_VALUE(os.str(), "5 55");
}

FALCON_TEST_TO_MAIN(tuple_for_each_test)
