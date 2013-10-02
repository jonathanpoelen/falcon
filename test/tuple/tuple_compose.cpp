#include <test/test.hpp>
#include <falcon/tuple/tuple_compose.hpp>
#include <falcon/iostreams/put_and_get.hpp>
#include <falcon/utility/maker.hpp>
#include "tuple_compose.hpp"

#include <sstream>
#include <tuple>

struct unless_functor
{
	template<typename... _Args>
	void operator()(const _Args&... args) const
	{ STATIC_ASSERT(sizeof...(args) == 2); }
};

void tuple_compose_test()
{
	std::ostringstream os;
	falcon::tuple_compose(
		unless_functor(),
		std::make_tuple(
			falcon::make_ostream_functor(os),
			falcon::make_ostream_functor(os)
		),
		std::make_tuple(5, ' ', 55)
	);

	CHECK_EQUAL_VALUE(os.str(), "5 555 55");

    os.str("");
    falcon::tuple_compose(
        falcon::parameter_index<0,1,2>(),
        unless_functor(),
        std::make_tuple(
            falcon::make_ostream_functor(os),
            falcon::make_ostream_functor(os)
        ),
        std::make_tuple(5, ' ', 55)
    );

    CHECK_EQUAL_VALUE(os.str(), "5 555 55");

	{
		os.str("");
		auto fos = falcon::make_ostream_functor(os);
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
