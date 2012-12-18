#ifndef FALCON_LITERAL_STRING_HPP
#define FALCON_LITERAL_STRING_HPP

#include <falcon/literal/detail/literal_support.hpp>

#include <string>

namespace falcon {
namespace literal {
namespace string {

#define FALCON_USER_DEFINED_STRING_LITERAL(char_type)\
	inline std::basic_string<char_type>\
	operator "" _s(const char_type * s, std::size_t len)\
	{ return std::basic_string<char_type>(s, len); }\
	\
	inline std::basic_string<char_type> operator "" _s(char_type c)\
	{ return std::basic_string<char_type>(c, 1); }

FALCON_USER_DEFINED_STRING_LITERAL(char)
FALCON_USER_DEFINED_STRING_LITERAL(wchar_t)
#ifndef BOOST_NO_UNICODE_LITERALS
FALCON_USER_DEFINED_STRING_LITERAL(char16_t)
FALCON_USER_DEFINED_STRING_LITERAL(char32_t)
#endif

#undef FALCON_USER_DEFINED_STRING_LITERAL

}
}
}

#endif