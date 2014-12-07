#include <test/test.hpp>
#include <vector>
#include <sstream>
#include <functional>
#include <falcon/algorithm/for_each2.hpp>
#include "for_each2.hpp"

void for_each2_test()
{
  using falcon::for_each2;

  std::stringstream ss;
	auto f = [&ss](int i, int i2){ ss << i << '-' << i2 << ' ';};
	{
		int a1[] = {1,2,3};
		std::vector<int> a2{{0,1,2,3}};

		for_each2(a1, a2, f);
		for_each2(a1, a2.begin(), f);
		for_each2(std::begin(a1), std::end(a1), a2, f);
		for_each2(std::begin(a1), std::end(a1), std::begin(a2), std::end(a2), f);
		for_each2(std::begin(a1), std::end(a1), std::begin(a2), f);
		for_each2(a1, std::begin(a2), std::end(a2), f);
		for_each2(a1, std::begin(a2), f);

		for_each2(a2, a1, f);
		for_each2(std::begin(a2), std::end(a2), a1, f);
		for_each2(std::begin(a2), std::end(a2), std::begin(a1), std::end(a1), f);
	}
	{
		int a1[] = {1,2,3};
		int a2[] = {0,1,2,3};
		for_each2(a1, &a2[0], f);
	}

	CHECK_EQUAL_VALUE(ss.str(), "1-0 2-1 3-2 1-0 2-1 3-2 1-0 2-1 3-2 1-0 2-1 3-2 1-0 2-1 3-2 1-0 2-1 3-2 1-0 2-1 3-2 0-1 1-2 2-3 0-1 1-2 2-3 0-1 1-2 2-3 1-0 2-1 3-2 ");
}

FALCON_TEST_TO_MAIN(for_each2_test)
