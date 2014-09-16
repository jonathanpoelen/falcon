#include <test/test.hpp>
#include <string>
#include <falcon/cstring.hpp>
#include <falcon/string/concat.hpp>
#include "concat.hpp"

void concat_test()
{
	char s[] = "i";
	falcon::cstring cs(s);
	falcon::const_cstring ccs2(cs);
	std::string ret = falcon::concat(
    std::string(),
		falcon::const_cstring("plo"),
		"p",
		std::string("lala"),
		cs,
		ccs2,
		'a'
	);
	CHECK_EQUAL_VALUE(ret, "ploplalaiia");
	ret = falcon::concat(ret, cs);
	CHECK_EQUAL_VALUE(ret, "ploplalaiiai");
	std::string ret2 = falcon::concat(std::move(ret), cs);
  CHECK_EQUAL_VALUE(ret2, "ploplalaiiaii");
	CHECK_EQUAL_VALUE(ret, "");
}

FALCON_TEST_TO_MAIN(concat_test)
