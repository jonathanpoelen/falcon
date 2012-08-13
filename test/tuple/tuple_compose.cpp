#include <test/test.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/iostream/put_and_get.hpp>
#include <falcon/functional/unless_functor.hpp>
#include "tuple_compose.hpp"

#include <sstream>

void tuple_compose_test()
{
	std::ostringstream os;
	falcon::tuple_compose<>(
		falcon::unless_functor(),
		std::make_tuple<>(
			falcon::make_ostream_functor(os),
			falcon::make_ostream_functor(os)
		),
		std::make_tuple<>(5, ' ', 55)
	);

	CHECK_EQUAL_VALUE(os.str(), "5 555 55");
}

FALCON_TEST_TO_MAIN(tuple_compose_test)
