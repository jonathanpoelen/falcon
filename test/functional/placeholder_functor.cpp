#include <functional>
#include <falcon/functional/placeholder_functor.hpp>
#include <falcon/utility/to_cref.hpp>
#include <falcon/iostream/iostream.hpp>
#include <test/test.hpp>
#include "placeholder_functor.hpp"

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

void placeholder_functor_test()
{
	std::ostringstream oss;
	{
		falcon::placeholder_functor<0, Out, char> f('<', &oss);
		f(0,1);
	}
	{
		falcon::placeholder_functor<1, Out, char> f('-', &oss);
		f(2,3);
	}
	{
		falcon::placeholder_functor<2, Out, char> f('>', &oss);
		f(4,5);
	}
	{
		falcon::placeholder_functor<0, const Out, char> f('<', &oss);
		f(0,1);
	}
	{
		falcon::placeholder_functor<1, const Out, char> f('-', &oss);
		f(2,3);
	}
	{
		falcon::placeholder_functor<2, const Out, char> f('>', &oss);
		f(4,5);
	}
	CHECK_EQUAL_VALUE("<012-345>@<01@2-3@45>", oss.str());

	CHECK_EQUAL_VALUE(4, falcon::placeholder_functor<0, falcon::late_divides, int>(20)(5));
	CHECK_EQUAL_VALUE(4, falcon::placeholder_functor<1, falcon::late_divides, int>(5)(20));
	CHECK_EQUAL_VALUE(4, falcon::placeholder_functor<-1, falcon::late_divides, int>(5)(20));
}

FALCON_TEST_TO_MAIN(placeholder_functor_test)
