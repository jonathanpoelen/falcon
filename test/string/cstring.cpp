#include <test/test.hpp>
#include <falcon/string/cstring.hpp>
#include "cstring.hpp"

void basic_cstring_test()
{
	{
		falcon::const_cstring cstr = "plop";
		CHECK(cstr == "plop");
		CHECK(cstr <= "plop");
		CHECK(cstr >= "plop");
		CHECK("plop" <= cstr);
		CHECK("plop" >= cstr);
	}
	{
		char s[] = {'p','l','o','p','\0'};
		falcon::cstring cstr(s);
		CHECK(cstr == "plop");
		CHECK(cstr <= "plop");
		CHECK(cstr >= "plop");
		CHECK("plop" <= cstr);
		CHECK("plop" >= cstr);
	}
	{
		falcon::const_cstring cstr = "abcd";
		CHECK(cstr != "bcd");
		CHECK("bcd" != cstr);
		CHECK(cstr < "bcd");
		CHECK("bcd" > cstr);
	}
}

FALCON_TEST_TO_MAIN(basic_cstring_test)
