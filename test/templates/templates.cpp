#include <falcon/templates.hpp>
#include "test.hpp"
#include "templates.hpp"

#if __cplusplus >= 201103L
#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/operators.hpp>

template<typename _T, typename _U>
struct static_value
{
	static const bool value = 1;
};

void templates_test()
{
	STATIC_CHECK_VALUE(true, falcon::template_or<std::is_pointer, std::is_integral>::filter<int>);
	STATIC_CHECK_VALUE(false, falcon::template_and<std::is_pointer, std::is_integral>::filter<int>);
	STATIC_CHECK_VALUE(true, falcon::template_or<static_value>::filter<int, int>);
	STATIC_CHECK_VALUE(false, falcon::template_not<falcon::template_or<static_value>::filter>::filter<int, int>);
	STATIC_CHECK_VALUE(false, falcon::template_binary<falcon::equal_to<>, std::is_pointer, std::is_integral>::value_wrapper<int>);
	STATIC_CHECK_VALUE(true, falcon::template_unary<falcon::logical_not<>, std::is_pointer>::value_wrapper<int>);
	STATIC_CHECK_VALUE(true, falcon::template_left_accumulator<falcon::template_or<static_value>::filter, int>::value_wrapper<int>);
	STATIC_CHECK_VALUE(true, falcon::template_right_accumulator<falcon::template_or<static_value>::filter, int>::value_wrapper<int>);
	STATIC_CHECK_VALUE(6, falcon::template_size<int,int,int,int,int,int>);
	STATIC_CHECK_VALUE(15u, falcon::template_binary<falcon::plus<>, falcon::template_size, falcon::template_val<std::size_t, 10>::filter>::value_wrapper<int,int,int,int,int>);

	STATIC_CHECK_VALUE(1, falcon::template_to_val<std::rank>::filter<int[]>);

	CHECK_EQUAL_VALUE(6u, falcon::template_binary<
		falcon::multiplies<>,
		falcon::template_to_val<
			std::rank
		>::filter,
		falcon::template_val<std::size_t, 3>::filter
	>::value_wrapper<int[4][8]>::value);
}
#else

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_integral.hpp>

template<typename _T>
struct static_value
{
	static const bool value = 1;
	typedef bool type;
};

template<typename _T,typename _U>
struct static_value2
{
	static const int value = 2;
	typedef int type;
};

void templates_test()
{
	STATIC_CHECK_VALUE(true, falcon::template_or<boost::is_pointer, boost::is_integral>::filter<int>);
	STATIC_CHECK_VALUE(false, falcon::template_and<boost::is_pointer, boost::is_integral>::filter<int>);
	STATIC_CHECK_VALUE(true, falcon::template_or<static_value>::filter<int>);
	STATIC_CHECK_VALUE(false, falcon::template_not<static_value>::filter<int>);
	STATIC_CHECK_VALUE(2, falcon::template_left_accumulator<static_value2, int>::value_wrapper<int>);
	STATIC_CHECK_VALUE(2, falcon::template_right_accumulator<static_value2, int>::value_wrapper<int>);
	STATIC_CHECK_VALUE(1, falcon::template_to_val<static_value>::filter<int[]>);
}
#endif

FALCON_TEST_TO_MAIN(templates_test)
