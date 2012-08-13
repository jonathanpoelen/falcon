#include <test/test.hpp>
#include <iostream>
#include <type_traits>
#include <falcon/templates/recursive_template.hpp>
#include <falcon/templates/loop_template.hpp>
#include "loop_template.hpp"

template <typename _T>
struct loop_template_test_remainder
{
	typedef typename std::remove_pointer<_T>::type type;
	static const std::size_t value = falcon::recursive_template<std::is_pointer, std::remove_pointer>::type_wrapper<_T>::depth - 1;
};

void loop_template_test()
{
	{
		std::cout << std::is_same<falcon::loop_template<2, std::remove_pointer>::type_wrapper<int***>, int*>::value << std::endl;
		std::cout << falcon::loop_template<4, loop_template_test_remainder>::value_wrapper<int****>::value << std::endl;
	}
}

FALCON_TEST_TO_MAIN(loop_template_test)
