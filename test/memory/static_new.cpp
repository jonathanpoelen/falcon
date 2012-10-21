#include <test/test.hpp>
#include <test/A.h>
#include <falcon/memory/static_new.hpp>
#include "static_new.hpp"

void static_new_test() {
	std::stringstream ss;
	std::streambuf* oldbuf = std::cout.rdbuf(ss.rdbuf());

	falcon::static_new<A[2]> snew;
	snew.construct(falcon::emplace, 0, 1);

	std::cout << snew.get()[0] << '\n';
	std::cout << snew.get()[1] << '\n';

	snew.destroy();
	CHECK_EQUAL_VALUE(ss.str(), "A(0)\nA(1)\nA::operator int() const\n0\nA::operator int() const\n1\n~A(1)\n~A(0)\n");

	std::cout.rdbuf(oldbuf);
}

FALCON_TEST_TO_MAIN(static_new_test)
