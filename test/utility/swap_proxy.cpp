#include <falcon/utility/swap_proxy.hpp>
#include "../test.hpp"
#include "swap_proxy.hpp"

template<typename _T>
struct F
{
	_T v;

	F(_T __v)
	:v(__v)
	{}

	template<typename _U>
	bool operator==(_U __v)
	{
		return __v >= v && __v <= v;
	}

	operator _T()
	{ return v; }
};

void swap_proxy_test()
{
	{
		struct A
		{
			int i;
			A(int __i):i(__i){}
			operator int() {return i;}
		};
		struct B
		{
			int i;
			operator int() {return i;}
			B(int __i):i(__i){}
			B(A a):i(a.i){}
		};

		A a = {1};
		B b = {56};

		falcon::swap_proxy<B, A, int>(b, a);
		CHECK_EQUAL_VALUE(56, a.i);
		CHECK_EQUAL_VALUE(1, b.i);
	}

	{
		double d = 484.578848;
		float f = 4.448f;

		falcon::swap_proxy<double, float, int>(d, f);
		CHECK_EQUAL_VALUE(F<double>(float(4.448)), d);
		CHECK_EQUAL_VALUE(F<float>(484), f);
	}
	{
		int i[] = {5,45,4,4,56};
		float f[] = {54.5f, 450.47f, .54545f, .45f, 4.f};

		falcon::swap_proxy<>(i, f);
		CHECK_EQUAL_VALUE(54, i[0]);
		CHECK_EQUAL_VALUE(450, i[1]);
		CHECK_EQUAL_VALUE(0, i[2]);
		CHECK_EQUAL_VALUE(0, i[3]);
		CHECK_EQUAL_VALUE(4, i[4]);
		CHECK_EQUAL_VALUE(F<float>(5), f[0]);
		CHECK_EQUAL_VALUE(F<float>(45), f[1]);
		CHECK_EQUAL_VALUE(F<float>(4), f[2]);
		CHECK_EQUAL_VALUE(F<float>(4), f[3]);
		CHECK_EQUAL_VALUE(F<float>(56), f[4]);
	}
}

FALCON_TEST_TO_MAIN(swap_proxy_test)
