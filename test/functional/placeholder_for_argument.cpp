#include <functional>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/iostreams/iostream.hpp>
#include <test/test.hpp>
#include "placeholder_for_argument.hpp"

struct Out
{
	std::ostringstream *oss;

	template<typename... _Args>
	void operator()(const _Args&... args)
	{
		falcon::put<>(*oss, args...);
	}
	template<typename... _Args>
	void operator()(const _Args&... args) const
	{
		falcon::put<>(*oss, '@', args...);
	}
};

void placeholder_for_argument_test()
{
	std::ostringstream oss;
	{
		falcon::placeholder_for_argument<0, Out, char>('[', &oss)(']');
		falcon::placeholder_for_argument<1, Out, char>(')', &oss)('(');
	}
	{
		falcon::placeholder_for_argument<0, Out, char> f('<', &oss);
		f(0,1);
	}
	{
		falcon::placeholder_for_argument<1, Out, char> f('-', &oss);
		f(2,3);
	}
	{
		falcon::placeholder_for_argument<2, Out, char> f('>', &oss);
		f(4,5);
	}
	{
		falcon::placeholder_for_argument<0, const Out, char> f('<', &oss);
		f(0,1);
	}
	{
		falcon::placeholder_for_argument<1, const Out, char> f('-', &oss);
		f(2,3);
	}
	{
		falcon::placeholder_for_argument<2, const Out, char> f('>', &oss);
		f(4,5);
	}
	{
		char c = '$';
		falcon::placeholder_for_argument<0, Out, char&> f(c, &oss);
		f(0,1);
		c = '#';
		f(2,3);
	}
	CHECK_EQUAL_VALUE("[]()<012-345>@<01@2-3@45>$01#23", oss.str());

	CHECK_EQUAL_VALUE(4, falcon::placeholder_for_argument<0, falcon::late_divides, int>(20)(5));
	CHECK_EQUAL_VALUE(4, falcon::placeholder_for_argument<1, falcon::late_divides, int>(5)(20));
	CHECK_EQUAL_VALUE(4, falcon::placeholder_for_argument<-1, falcon::late_divides, int>(5)(20));

	int n = 3;
	falcon::placeholder_for_argument<1, falcon::plus_equal<int>, int>(4)(n);
	CHECK_EQUAL_VALUE(n, 7);
}

FALCON_TEST_TO_MAIN(placeholder_for_argument_test)
