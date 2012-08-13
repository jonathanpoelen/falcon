#include <test/test.hpp>
#include <falcon/tuple/to_tuple_reference.hpp>
#include "to_tuple_reference.hpp"

void to_tuple_reference_test()
{
	typedef std::tuple<int, int, long> tuple_type;
	typedef std::tuple<int&, int&, long&> reference_type;

	tuple_type t(5,9,10);
	auto tref = falcon::to_tuple_reference<>(t);

	CHECK_NOTYPENAME_TYPE(reference_type, decltype(tref));
}
FALCON_TEST_TO_MAIN(to_tuple_reference_test)
