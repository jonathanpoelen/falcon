#include <test/test.hpp>
#include <array>
#include <vector>
#include <sstream>
#include <falcon/functional/operators.hpp>
#include <falcon/algorithm/recursive_for_each.hpp>
#include <falcon/lambda/lambda.hpp>
#include "recursive_for_each.hpp"

namespace alg = falcon::algorithm;

void recursive_for_each_test(/*int argc, char **argv*/)
{
	typedef falcon::decrement<int> func_type;
	typedef falcon::bit_not<int> filter_type;
	typedef std::array<int, 5> subarray;
	std::vector<subarray> v{{
		{{1,2,3,4,5}},
		{{1,2,3,4,5}},
		{{1,2,3,4,5}},
		{{1,2,3,4,5}}
  }};
	std::stringstream oss;
	auto print = oss << falcon::lambda::placeholders::_1 << ',';

	alg::recursive_for_each(v, print);
  CHECK_EQUAL_VALUE("1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,", oss.str());
  oss.str("");
	alg::recursive_for_each(v, func_type());
	alg::recursive_for_each(v, print);
  CHECK_EQUAL_VALUE("0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,", oss.str());
  oss.str("");
  alg::recursive_for_each(v, alg::break_if(func_type(), filter_type()));
	alg::recursive_for_each(v, print);
  CHECK_EQUAL_VALUE("-1,1,2,3,4,-1,1,2,3,4,-1,1,2,3,4,-1,1,2,3,4,", oss.str());
  oss.str("");
  alg::recursive_for_each<1>(v, alg::recursive_intermediate(
		falcon::lambda::lambda(oss) << '[',
		print,
		falcon::lambda::lambda(oss) << ']'
	));
  CHECK_EQUAL_VALUE("[-1,1,2,3,4,][-1,1,2,3,4,][-1,1,2,3,4,][-1,1,2,3,4,]", oss.str());
  oss.str("");

	alg::recursive_for_each(v, alg::return_off(func_type(), 4));
	alg::recursive_for_each(v, print);
  CHECK_EQUAL_VALUE("-2,0,1,2,4,-1,1,2,3,4,-1,1,2,3,4,-1,1,2,3,4,", oss.str());
}
FALCON_TEST_TO_MAIN(recursive_for_each_test)
