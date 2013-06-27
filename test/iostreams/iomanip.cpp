#include <sstream>
#include <test/test.hpp>
#include <falcon/iostreams/iomanip.hpp>
#include <falcon/lambda/lambda.hpp>
#include "iomanip.hpp"

void iomanip_test()
{
	{
		std::stringstream ss(" ");
		ss << "  " << 1 << falcon::endl;
		CHECK_EQUAL_VALUE(ss.str(), "  1\n");
		ss.unsetf(std::ios::skipws);
		char c;
		ss >> c;
		CHECK_EQUAL_VALUE(c, ' ');
		ss >> falcon::ws >> c;
		CHECK_EQUAL_VALUE(c, '1');
	}

	{
		using falcon::lambda::lambda;
		using namespace falcon::lambda::placeholders;
		std::wstringstream wss;
		auto p3 = lambda(wss) << _1 << falcon::endl;
		p3(56);
		CHECK(wss.str() == L"56\n");
	}
}

FALCON_TEST_TO_MAIN(iomanip_test)
