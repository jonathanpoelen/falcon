#include <test/test.hpp>
#include <array>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/ostream/join.hpp>
#include "join.hpp"

template<typename _T>
void __join_test(_T& arr)
{
	std::stringstream ss;
	std::string s;

	ss.width(4);
	falcon::ostream::join<>(ss, arr, ':') << std::endl;
	s += "  18:  19:   0:   1\n";
	ss.width(4);
	ss.flags(std::ios::left);
	ss << falcon::ostream::join<>(arr, ':') << std::endl;
	s += "18  :19  :0   :1   \n";

	falcon::ostream::join<>(ss, arr, "::", 1) << std::endl;
	s += "18:19:0:1\n";
	ss << falcon::ostream::join<>(arr, "::", 1) << std::endl;
	s += "18:19:0:1\n";

	falcon::ostream::join<>(ss, arr, ":") << std::endl;
	s += "18:19:0:1\n";
	ss << falcon::ostream::join<>(arr, ":") << std::endl;
	s += "18:19:0:1\n";

	falcon::ostream::join<>(ss, falcon::begin(arr), falcon::end(arr), ':') << std::endl;
	s += "18:19:0:1\n";
	ss << falcon::ostream::join<>(falcon::begin(arr), falcon::end(arr), ':') << std::endl;
	s += "18:19:0:1\n";

	falcon::ostream::join<>(ss, falcon::begin(arr), falcon::end(arr), "::", 1) << std::endl;
	s += "18:19:0:1\n";
	ss << falcon::ostream::join<>(falcon::begin(arr), falcon::end(arr), "::", 1) << std::endl;
	s += "18:19:0:1\n";

	falcon::ostream::join<>(ss, falcon::begin(arr), falcon::end(arr), ":") << std::endl;
	s += "18:19:0:1\n";
	ss << falcon::ostream::join<>(falcon::begin(arr), falcon::end(arr), ":") << std::endl;
	s += "18:19:0:1\n";

	CHECK_EQUAL_VALUE(s, ss.str());
}

void join_test()
{
	{
		typedef std::array<int, 4> container_type;
		container_type arr{{18,19,0,1}};
		__join_test<container_type>(arr);
	}
	{
		typedef int container_type[4];
		container_type arr{18,19,0,1};
		__join_test<container_type>(arr);
	}
}
FALCON_TEST_TO_MAIN(join_test)
