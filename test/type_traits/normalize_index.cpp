#include <test/test.hpp>
#include <falcon/type_traits/normalize_index.hpp>
#include "normalize_index.hpp"

void normalize_index_test()
{
	using falcon::normalize_index;

	STATIC_CHECK_VALUE(0, normalize_index<0, 5>);
	STATIC_CHECK_VALUE(1, normalize_index<1,3>);
	STATIC_CHECK_VALUE(2, normalize_index<2,3>);
	//STATIC_CHECK_VALUE(0, normalize_index<3,3>);
	STATIC_CHECK_VALUE(2, normalize_index<-1,3>);
	STATIC_CHECK_VALUE(1, normalize_index<-2,3>);
	STATIC_CHECK_VALUE(0, normalize_index<-3,3>);
	//STATIC_CHECK_VALUE(0, normalize_index<9,3>);
	//STATIC_CHECK_VALUE(1, normalize_index<10,3>);

}

FALCON_TEST_TO_MAIN(normalize_index_test)
