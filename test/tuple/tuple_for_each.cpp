#include <tuple>
#include <test/test.hpp>
#include <falcon/tuple/tuple_for_each.hpp>
#include <falcon/iostreams/sput.hpp>
#include <falcon/functional/invoker.hpp>
#include "tuple_for_each.hpp"

void tuple_for_each_test()
{
	std::ostringstream os;
  auto put = falcon::make_invoker(falcon::iostreams::sput, std::ref(os));
	falcon::tuple_for_each(std::make_tuple(5, ' ', 55), put);
	CHECK_EQUAL_VALUE(os.str(), "5 55");
}

FALCON_TEST_TO_MAIN(tuple_for_each_test)
