#include <test/test.hpp>
#include <falcon/type_traits/add_n_pointer.hpp>
#include "add_n_pointer.hpp"

void add_n_pointer_test()
{
	using falcon::add_n_pointer;
	CHECK_TYPE(int****,	add_n_pointer<int, 4>);
	CHECK_TYPE(int****,	add_n_pointer<int*, 3>);
	CHECK_TYPE(const int***, add_n_pointer<const int*, 2>);
	CHECK_TYPE(const int* const**, add_n_pointer<const int* const, 2>);
	CHECK_TYPE(volatile int **, add_n_pointer<volatile int, 2>);
}

FALCON_TEST_TO_MAIN(add_n_pointer_test)
