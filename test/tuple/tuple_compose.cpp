#include <test/test.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/iostream/put_and_get.hpp>
#include "tuple_compose.hpp"

#include <sstream>

struct unless_functor
{
	template<typename _T>
	const _T& operator()(const _T& a) const
	{ return a; }

	void operator()() const
	{}
};

void tuple_compose_test()
{
	std::ostringstream os;
	falcon::tuple_compose<>(
		unless_functor(),
		std::make_tuple<>(
			falcon::make_ostream_functor(os),
			falcon::make_ostream_functor(os)
		),
		std::make_tuple<>(5, ' ', 55)
	);

	CHECK_EQUAL_VALUE(os.str(), "5 555 55");
}

FALCON_TEST_TO_MAIN(tuple_compose_test)
