#ifndef FALCON_LITERAL_CSTRING_HPP
#define FALCON_LITERAL_CSTRING_HPP

#include <falcon/literal/detail/literal_support.hpp>

#include <falcon/string/basic_cstring.hpp>

namespace falcon {
namespace literal {
namespace string {

#define FALCON_USER_DEFINED_CSTRING_LITERAL(char_type)\
	inline constexpr ::falcon::basic_cstring<char_type>\
	operator "" _cs(const char_type * s, std::size_t len) noexcept\
	{ return ::falcon::basic_cstring<char_type>(s, len); }\
	\
	inline constexpr ::falcon::basic_cstring<char_type>\
	operator "" _cs(char_type c) noexcept\
	{ return ::falcon::basic_cstring<char_type>(&c, 1); }

FALCON_USER_DEFINED_CSTRING_LITERAL(char)
FALCON_USER_DEFINED_CSTRING_LITERAL(wchar_t)
#ifndef BOOST_NO_UNICODE_LITERALS
FALCON_USER_DEFINED_CSTRING_LITERAL(char16_t)
FALCON_USER_DEFINED_CSTRING_LITERAL(char32_t)
#endif

#undef FALCON_USER_DEFINED_CSTRING_LITERAL

}
}
}

#endif
