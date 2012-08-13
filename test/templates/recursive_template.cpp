#include <test/test.hpp>
#include <falcon/templates/recursive_template.hpp>
#include "recursive_template.hpp"

template <typename _T>
struct remove_pointer
{
	typedef typename std::remove_pointer<_T>::type type;
	static const std::size_t value = 5;
};

void recursive_template_test()
{
	{
		typedef falcon::recursive_template<
			std::is_pointer,
			remove_pointer
		> remove_all_extents_wrapper;
		CHECK_TYPE(int, remove_all_extents_wrapper::type_wrapper<int***>);
		CHECK_EQUAL_VALUE(5, remove_all_extents_wrapper::value_wrapper<int***>::value);
		CHECK_EQUAL_VALUE(4, remove_all_extents_wrapper::type_wrapper<int***>::depth);
	}
	{
		typedef falcon::recursive_template<
			std::is_pointer,
			remove_pointer,
			2
		> remove_all_extents_wrapper;
		CHECK_TYPE(int*, remove_all_extents_wrapper::type_wrapper<int***>);
		CHECK_EQUAL_VALUE(5, remove_all_extents_wrapper::value_wrapper<int***>::value);
		CHECK_EQUAL_VALUE(2, remove_all_extents_wrapper::type_wrapper<int***>::depth);
	}
	/*{
		//NOTE force assertion error
		typedef falcon::recursive_template<
			std::is_pointer,
			std::remove_pointer,
			-1,
			true
		> remove_all_extents_wrapper;
		CHECK_TYPE(int, remove_all_extents_wrapper::type_wrapper<int>);
	}*/
}
FALCON_TEST_TO_MAIN(recursive_template_test)
