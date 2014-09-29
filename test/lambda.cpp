#include <iostream>
#include <vector>
#include <sstream>
#include <boost/preprocessor/stringize.hpp>
#include <test/test.hpp>
#include <falcon/lambda.hpp>
#include <falcon/iostreams/resolve_manipulator.hpp>
#include "A.h"
#include "lambda.hpp"

#define LAMBDA_TEST(_Result, _Lambda, ...)\
	CHECK_EQUAL_VALUE(_Result, ((_Lambda)(__VA_ARGS__)))

static double lambda_f2(int i, double d)
{
	return d+i;
}

struct B
{
	int f(int n)
	{return n;}
};

namespace phr = falcon::lambda::placeholders;

void lambda_test() {
	LAMBDA_TEST(-5,	-phr::_1, 5);
	LAMBDA_TEST(10,	phr::_1 + phr::_1, 5);
	LAMBDA_TEST(7,	phr::_1 + phr::_2, 5,2);
	LAMBDA_TEST(15,	phr::_1 + phr::_2 * phr::_1, 5,2);
	LAMBDA_TEST(27,	phr::_1 * phr::_1 + phr::_2, 5,2);
	LAMBDA_TEST(50,	phr::_1 * phr::_1 * phr::_2, 5,2);
	LAMBDA_TEST(50,	phr::_1 * (phr::_1 * phr::_2), 5,2);
	LAMBDA_TEST(100,phr::_1 * phr::_1 * phr::_2 * phr::_2, 5,2);
	LAMBDA_TEST(100,(phr::_1 * phr::_1) * (phr::_2 * phr::_2), 5,2);

	{
		int i = 1;
		auto ref = std::ref(i);
		{
			auto f = phr::_1 + ref;
			LAMBDA_TEST(6, f, 5);
			i = 2;
			LAMBDA_TEST(7, f, 5);
		}
		{
			auto f = ref + phr::_1;
			LAMBDA_TEST(7, f, 5);
			i = 1;
			LAMBDA_TEST(6, f, 5);
		}
	}
	LAMBDA_TEST(6,	1 + phr::_1, 5);
	LAMBDA_TEST(8,	phr::_1 + 1 + 2, 5);
	LAMBDA_TEST(12,	phr::_1 + phr::_1 + 2, 5);
	LAMBDA_TEST(11,	1 + phr::_1 + phr::_1, 5);

	{
		std::vector<unsigned> v CPP1X(1,2,3,4,5,6,7,8,9);
		unsigned index = 0;
		auto ref = std::ref(index);
		auto f = phr::_1[ref];
		LAMBDA_TEST(1u, f, v);
		LAMBDA_TEST(2u, phr::_1 = phr::_2, index, 2u);
		LAMBDA_TEST(3u, f, v);
		LAMBDA_TEST(5u, phr::_1 = 5u, index);
		LAMBDA_TEST(6u, f, v);
		LAMBDA_TEST(9u, phr::_1->*&std::vector<unsigned>::size, v);
	}
	{
		B b;
		LAMBDA_TEST(2, phr::_2->*&B::f, 2,b);
	}

	{
		LAMBDA_TEST(-6, -(1 + phr::_1), 5);
		LAMBDA_TEST(~6, ~(1 + phr::_1), 5);
		LAMBDA_TEST(-6 + ~6, -(1 + phr::_1) + ~(1 + phr::_1), 5);
	}

	{
		A a;
		std::stringstream ss;
		auto f = ss << phr::_1 << a;
		f(4);
		f(48);
		std::stringstream ss2;
		ss2 << 4 << a << 48 << a;
		CHECK_EQUAL_VALUE(ss.str(), ss2.str());
	}
	{
		std::stringstream ss;
		auto f = ss << phr::_1 << A();
		f(4);
		f(48);
		std::stringstream ss2;
		ss2 << 4 << A() << 48 << A();
		CHECK_EQUAL_VALUE(ss.str(), ss2.str());
	}

	{
		using falcon::lambda::lambda;
		std::stringstream ss;
		auto f = lambda(ss) << '[' << phr::_1 << "]\n";
		f(5);
		f("plop");
		f(8);
		CHECK_EQUAL_VALUE(ss.str(), "[5]\n[plop]\n[8]\n");
	}

	{
		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = -f;
			LAMBDA_TEST(-10, lambda_f2, 4,6,4);
		}

		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = f+f;
			LAMBDA_TEST(20, lambda_f2, 4,6,4);
		}

		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = f + phr::_1;
			LAMBDA_TEST(14, lambda_f2, 4,6,4);
		}

		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = phr::_1 + f;
			LAMBDA_TEST(14, lambda_f2, 4,6,4);
		}

		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = (phr::_1 + f) + phr::_3;
			LAMBDA_TEST(18, lambda_f2, 4,6,4);
		}

		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = phr::_1 + (f + phr::_3);
			LAMBDA_TEST(18, lambda_f2, 4,6,4);
		}

		{
			using namespace std::placeholders;
			auto f = std::bind(falcon::plus<>(), _1, _2);
			auto lambda_f2 = (f + phr::_1) + (f + phr::_3);
			LAMBDA_TEST(28, lambda_f2, 4,6,4);
		}

		CHECK_EQUAL_VALUE(16, static_cast<int>((phr::_2 + falcon::lambda::lambda_bind<>(lambda_f2))(4,6)));
	}

	{
		std::stringstream ss;
		std::wstringstream wss;
		using falcon::iostreams::resolve_manipulator;
		(ss << phr::_1 << resolve_manipulator<char>(std::endl))(4);
		(wss << phr::_1 << resolve_manipulator<wchar_t>(std::endl))(4);
		(ss << phr::_1 << resolve_manipulator(ss, std::endl))(4);
		(wss << phr::_1 << resolve_manipulator(wss, std::endl))(4);
		CHECK_EQUAL_VALUE(ss.str(), "4\n4\n");
		if (wss.str() != L"4\n4\n")
			throw std::runtime_error(BOOST_PP_STRINGIZE(__LINE__));
	}

	{
		using namespace falcon::lambda;
		using namespace placeholders;

		{
			//Fibonacci
			auto f = while_loop(
				--_1 > 0,
				(_2 = _3 + _4,
				 _3 = _4,
				 _4 = _2)
			);
			int n = 10, a = 0, b = 1, tmp;
			f(int(n), tmp, a, b);
			CHECK_EQUAL_VALUE(a, 34);
			CHECK_EQUAL_VALUE(b, 55);
		}
		{
			//Fibonacci
			auto f = for_loop(
				lambda(10),
				_1 > 0,
				(_2 = _3 + _4,
				 _3 = _4,
				 _4 = _2),
				 --_1
			);
			int a = 0, b = 1, tmp;
			f(tmp, a, b);
			CHECK_EQUAL_VALUE(a, 55);
			CHECK_EQUAL_VALUE(b, 89);
		}
		{
			std::stringstream ss;
			auto p3 = lambda(ss) << _1 << std::endl;
			p3(56);
			CHECK_EQUAL_VALUE(ss.str(), "56\n");
		}
		{
			std::wstringstream wss;
			auto p3 = lambda(wss) << _1 << std::endl;
			p3(56);
			CHECK(wss.str() == L"56\n");
		}
	}
}

FALCON_GROUP_TEST_TO_MAIN(lambda_test)
