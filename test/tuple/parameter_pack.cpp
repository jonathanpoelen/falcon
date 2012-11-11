#include <test/test.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include "parameter_pack.hpp"
#include <tuple>
#include <array>

void parameter_pack_test()
{
	typedef std::tuple<char, int, double, long, long long> tuple1;
	typedef falcon::build_range_tuple_to_parameter_pack<1, 4, tuple1>::type pack;
	CHECK_NOTYPENAME_TYPE(falcon::parameter_pack<int, double, long>, pack);
	CHECK_NOTYPENAME_TYPE(
		std::tuple<int, double, long>,
		falcon::parameter_pack_to_tuple<pack>::type
	);
	CHECK_NOTYPENAME_TYPE(
		falcon::parameter_pack<int, int>,
		falcon::tuple_to_parameter_pack<
			std::array<int ,2>
		>::type
	);
}

FALCON_TEST_TO_MAIN(parameter_pack_test)
