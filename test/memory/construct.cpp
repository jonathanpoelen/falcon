#include <test/test.hpp>
#include <falcon/memory/construct.hpp>
#include <falcon/memory/destroy.hpp>
#include "construct.hpp"

#include <array>

void construct_test()
{
	struct A
	{
		int x;
	};

	class B
	{
	public:
		int a,b;
		B(int x, int y)
		: a(x)
		, b(y)
		{}
	};

	using P = A[2];

	using C = std::array<int, 3>;

	A * p1 = falcon::default_new<A>(2);
	B * p2 = falcon::default_new<B>(4,3);
	P * p3 = falcon::default_new<P>(A{1},A{7});
	C * p4 = falcon::default_new<C>(5,6,8);

	CHECK(p1->x == 2);
	CHECK(p2->a == 4);
	CHECK(p2->b == 3);
	CHECK((*p3)[0].x == 1);
	CHECK((*p3)[1].x == 7);
	CHECK((*p4)[0] == 5);
	CHECK((*p4)[1] == 6);
	CHECK((*p4)[2] == 8);

	falcon::destroy<>(p1);
	falcon::destroy<>(p2);
	falcon::destroy<>(p3);
	falcon::destroy<>(p4);
}

FALCON_TEST_TO_MAIN(construct_test)
