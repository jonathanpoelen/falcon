#include <test/test.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/iostreams/sput.hpp>
#include <falcon/utility/maker.hpp>
#include <falcon/functional/invoker.hpp>
#include "tuple_compose.hpp"

#include <sstream>
#include <tuple>

struct unless_functor
{
	template<class... Args>
	void operator()(const Args&... args) const
	{ STATIC_ASSERT(sizeof...(args) == 2); }
};

void tuple_compose_test()
{
	std::ostringstream os;

	auto put = falcon::make_invoker(falcon::iostreams::sput, std::ref(os));

	falcon::tuple_compose(
		unless_functor(),
		std::make_tuple(put, put),
		std::make_tuple(5, ' ', 55)
	);

	CHECK_EQUAL_VALUE(os.str(), "5 555 55");

  os.str("");
  falcon::tuple_compose(
    falcon::parameter_index<0,1,2>(),
    unless_functor(),
    std::make_tuple(put, put),
    std::make_tuple(5, ' ', 55)
  );

  CHECK_EQUAL_VALUE(os.str(), "5 555 55");

	{
		os.str("");
		auto fos = put;
		auto tuple = std::make_tuple(5, ' ', 55);
		unless_functor f;
		falcon::tuple_compose(
			f,
			std::forward_as_tuple(fos, fos),
			tuple
		);
		CHECK_EQUAL_VALUE(os.str(), "5 555 55");
	}

	falcon::tuple_compose(
		unless_functor(),
		std::make_tuple(
			falcon::maker<int>(),
			falcon::maker<int>()
		)
	);

	falcon::tuple_compose(
		falcon::maker<std::pair<int,int>>(),
		std::make_tuple(
			falcon::maker<int>(),
			falcon::maker<int>()
		)
	);
}

FALCON_TEST_TO_MAIN(tuple_compose_test)
