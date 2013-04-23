#include <test/test.hpp>
#include <falcon/functional/arguments_wrapper.hpp>
#include "arguments_wrapper.hpp"

void arguments_wrapper_test()
{
	int a = 0, b = 2;
	falcon::arguments_wrapper<int&, int> arguments(a, b);
	arguments([](int &x, int& y){ x += ++y; });
	CHECK(a == 3);
	CHECK(b == 2);
	CHECK(std::get<0>(arguments) == 3);
	CHECK(std::get<1>(arguments) == 3);
}

FALCON_TEST_TO_MAIN(arguments_wrapper_test)
