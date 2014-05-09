#include "test/test.hpp"
#include <string>
#include <sstream>
#include <falcon/iostreams/ignore.hpp>
#include "ignore.hpp"

void ignore_test()
{
	std::istringstream ss("abcdef\ndefgo\n");
	std::string s;

	falcon::iostreams::ignore(ss, 3) >> s;
	CHECK_EQUAL_VALUE(s, "def");
	//NOTE discard all whitespace (here, first '\n')
	falcon::iostreams::ignore(std::ws(ss), s) >> s;
	CHECK_EQUAL_VALUE(s, "go");

	CHECK_EQUAL_VALUE(true, ss.good());

	ss.str("pliop");
	falcon::iostreams::laxignore(ss, "plop") >> s;
	CHECK_EQUAL_VALUE(s, "iop");

	CHECK_EQUAL_VALUE(true, ss.eof());

	ss.clear();
	ss.str("plop");
	falcon::iostreams::ignore(ss, [](int c){return c == int('p'); }) >> s;
	CHECK_EQUAL_VALUE(s, "lop");
	CHECK_EQUAL_VALUE(true, ss.eof());

	ss.clear();
	ss.str("plopiplop");
	falcon::iostreams::ignore_of(ss, "lop") >> s;
	CHECK_EQUAL_VALUE(s, "iplop");

	CHECK_EQUAL_VALUE(true, ss.eof());
}

FALCON_TEST_TO_MAIN(ignore_test)
