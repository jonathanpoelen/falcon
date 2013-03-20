#include <iostream>
#include <falcon/string/cstring.hpp>
#include <falcon/string/concat.hpp>

int main(/*int argc, char **argv*/)
{
// 	falcon::const_cstring ccs("plop");
	char s[] = "ids";
	falcon::cstring cs(s);
	falcon::const_cstring ccs2(cs);
	std::cout << falcon::concat<>(falcon::const_cstring("plo"),"p", std::string("lala")) << '\n';
	std::cout << falcon::concat<>('a',"p") << '\n';
	falcon::concat<>(std::string(), 'a',"p");
}
