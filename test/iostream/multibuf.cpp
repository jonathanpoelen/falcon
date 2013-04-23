#include <test/test.hpp>
#include <falcon/iostream/multibuf.hpp>
#include "multibuf.hpp"

void multibuf_test()
{
	std::stringbuf sb1("a:a\na\n");
	std::stringbuf sb2("b:b\nb");
	std::stringbuf sb3("plop");
	std::ostringstream oss;

	falcon::multistreambuf sbs(std::vector<std::streambuf*>({&sb1, &sb2, &sb3}));
	std::istream is(&sbs);
	is >> oss.rdbuf();
	CHECK_EQUAL_VALUE(oss.str(), "a:a\na\nb:b\nbplop");
}

FALCON_TEST_TO_MAIN(multibuf_test)
