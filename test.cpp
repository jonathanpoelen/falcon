#include <iostream>
#include <falcon/string/cstring.hpp>

struct A{};

int main(/*int argc, char **argv*/)
{
	char s[] = "plop";
	falcon::cstring cs(s);
	falcon::const_cstring ccs(cs);

	cs == ccs;
	cs.compare(ccs);
	ccs.compare(cs);
	ccs.find(cs);
	cs.find(ccs);
}
