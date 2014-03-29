#include <array>
#include <test/test.hpp>
#include <falcon/logical.hpp>
#include <falcon/logical/between_minmax.hpp>
#include "logical.hpp"

void logical_test()
{
	CHECK_EQUAL_VALUE(0,  falcon::between_minmax(-5,0,5));
	CHECK_EQUAL_VALUE(-5, falcon::between_minmax(-5,-10,5));
	CHECK_EQUAL_VALUE(5,  falcon::between_minmax(-5,10,5));

	STATIC_ASSERT(-1 == falcon::compare(0,1));
	STATIC_ASSERT(1 == falcon::compare(1,0));
	STATIC_ASSERT(2 == falcon::compare<1,3,2>(0,0));

	STATIC_ASSERT(2 == falcon::mcompare(0,-1,-2,-3, 2));

	STATIC_ASSERT(true  == falcon::between(-2,0,2));
	STATIC_ASSERT(false == falcon::between(-2,-2,2));
	STATIC_ASSERT(false == falcon::between(-2,2,2));

	STATIC_ASSERT(true  == falcon::inner(-2,0,2));
	STATIC_ASSERT(true  == falcon::inner(-2,-2,2));
	STATIC_ASSERT(true  == falcon::inner(-2,2,2));
	STATIC_ASSERT(false == falcon::inner(-2,-3,2));
	STATIC_ASSERT(false == falcon::inner(-2,3,2));

	STATIC_ASSERT(false == falcon::outside(-2,0,2));
	STATIC_ASSERT(false == falcon::outside(-2,2,2));
	STATIC_ASSERT(true  == falcon::outside(-2,-3,2));
	STATIC_ASSERT(true  == falcon::outside(-2,3,2));

	STATIC_ASSERT(false == falcon::inner_out(-2,0,2));
	STATIC_ASSERT(false == falcon::inner_out(-2,-1,2));
	STATIC_ASSERT(true  == falcon::inner_out(-2,2,2));
	STATIC_ASSERT(true  == falcon::inner_out(-2,-3,2));
	STATIC_ASSERT(true  == falcon::inner_out(-2,3,2));
}

FALCON_GROUP_TEST_TO_MAIN(logical_test)
