#ifndef FALCON_STRING_CSTRINGFW_HPP
#define FALCON_STRING_CSTRINGFW_HPP

namespace std {
	template<typename>
	class char_traits;
}

namespace falcon {
	template <typename _CharT, typename _Traits = std::char_traits<_CharT> >
	class basic_cstring;

	typedef basic_cstring<char> cstring; /// A cstring of @c char
	typedef basic_cstring<wchar_t> cwstring; /// A cstring of @c wchar_t

	typedef basic_cstring<const char> const_cstring; /// A cstring of @c const_char
	typedef basic_cstring<const wchar_t> const_cwstring; /// A cstring of @c const_wchar_t

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	typedef basic_cstring<char16_t> u16string; /// A cstring of @c char16_t
	typedef basic_cstring<char32_t> u32string; /// A cstring of @c char32_t

	typedef basic_cstring<const char16_t> const_u16string; /// A cstring of @c const_char16_t
	typedef basic_cstring<const char32_t> const_u32string; /// A cstring of @c const_char32_t
#endif
}

#endif