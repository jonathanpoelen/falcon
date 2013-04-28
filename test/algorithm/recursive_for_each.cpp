#include <test/test.hpp>
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
	typedef falcon::binary_negate<int> filter_type;
	typedef std::vector<int> subarray;
	std::vector<subarray> v(CPP1X(
		CPP1X(1,2,3,4,5),
		CPP1X(1,2,3,4,5),
		CPP1X(1,2,3,4,5),
		CPP1X(1,2,3,4,5)
	));
	std::stringstream oss;
	auto print = oss << falcon::lambda::placeholders::_1 << ',';
	std::string str;
	str.reserve(300);

	alg::recursive_for_each<>(v, print).left("\n");
	str += "1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,\n";
	CHECK_EQUAL_VALUE(str, oss.str());
	alg::recursive_for_each<>(v, func_type());
	alg::recursive_for_each<>(v, print).left("\n");
	str += "0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,\n";
	CHECK_EQUAL_VALUE(str, oss.str());
	alg::recursive_for_each<>(v, alg::break_if<>(func_type(), filter_type()));
	alg::recursive_for_each<>(v, print).left("\n");
	str += "-1,1,2,3,4,-1,1,2,3,4,-1,1,2,3,4,-1,1,2,3,4,\n";
	CHECK_EQUAL_VALUE(str, oss.str());
	alg::recursive_for_each<1>(v, alg::recursive_intermediate<>(
		falcon::lambda::lambda<>(oss) << '[',
		print,
		falcon::lambda::lambda<>(oss) << ']'
	));
	str += "[-1,1,2,3,4,][-1,1,2,3,4,][-1,1,2,3,4,][-1,1,2,3,4,]";
	CHECK_EQUAL_VALUE(str, oss.str());

	/*int *p = alg::return_recursive_for_each<int>(v, alg::break_off<>(func_type(), 4));
	CHECK(p);
	CHECK_EQUAL_VALUE(*p, 4);
	CHECK_EQUAL_VALUE(p, &(v[0][4]));*/

	alg::recursive_for_each<>(v, alg::return_off<>(func_type(), 4));
	alg::recursive_for_each<>(v, print).left('\n');
	str += "-2,0,1,2,4,-1,1,2,3,4,-1,1,2,3,4,-1,1,2,3,4,\n";
	CHECK_EQUAL_VALUE(str, oss.str());
}
FALCON_TEST_TO_MAIN(recursive_for_each_test)
