#include <test/test.hpp>
#include <string>
#include <falcon/string/cstring.hpp>
#include <falcon/string/append.hpp>
#include "append.hpp"

void append_test()
{
	char s[] = "i";
	falcon::cstring cs(s);
	falcon::const_cstring ccs2(cs);
	std::string ret("k");
	falcon::append(
		ret,
		falcon::const_cstring("plo"),
		"p",
		std::string("lala"),
		cs, ccs2
	);
	CHECK_EQUAL_VALUE(ret, "kploplalaii");
	falcon::append(ret, "i");
	CHECK_EQUAL_VALUE(ret, "kploplalaiii");
}

FALCON_TEST_TO_MAIN(append_test)
