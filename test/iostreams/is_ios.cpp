#include <falcon/iostreams/is_ios.hpp>
#include "test/test.hpp"
#include <fstream>
#include "is_ios.hpp"

void is_ios_test()
{
	using falcon::is_ostream;

	STATIC_CHECK_VALUE(true, falcon::is_ostream<std::wostream>);
	STATIC_CHECK_VALUE(true, falcon::is_ostream<std::ofstream>);
	STATIC_CHECK_VALUE(true, falcon::is_ostream<std::ostream>);
	STATIC_CHECK_VALUE(true, falcon::is_ostream<std::iostream>);
	STATIC_CHECK_VALUE(false, falcon::is_ostream<int>);
	STATIC_CHECK_VALUE(false, falcon::is_istream<std::ofstream>);
	STATIC_CHECK_VALUE(false, falcon::is_istream<std::ostream>);
	STATIC_CHECK_VALUE(true, falcon::is_istream<std::iostream>);
	STATIC_CHECK_VALUE(false, falcon::is_istream<int>);
	STATIC_CHECK_VALUE(false, falcon::is_iostream<std::ofstream>);
	STATIC_CHECK_VALUE(false, falcon::is_iostream<std::ostream>);
	STATIC_CHECK_VALUE(true, falcon::is_iostream<std::iostream>);
	STATIC_CHECK_VALUE(false, falcon::is_iostream<int>);
}

FALCON_TEST_TO_MAIN(is_ios_test)
