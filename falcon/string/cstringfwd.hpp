#ifndef FALCON_STRING_CSTRINGFW_HPP
#define FALCON_STRING_CSTRINGFW_HPP

namespace std {
	template<typename>
	class char_traits;
}

namespace falcon {

/**
 * @defgroup strings Strings
 *
 * @{
 */

template <typename _CharT, typename _Traits = std::char_traits<_CharT> >
class basic_cstring;

/// A cstring of @c char
typedef basic_cstring<char> cstring;
/// A cstring of @c wchar_t
typedef basic_cstring<wchar_t> cwstring;

/// A cstring of @c const_char
typedef basic_cstring<const char, std::char_traits<char> > const_cstring;
/// A cstring of @c const_wchar_t
typedef basic_cstring<const wchar_t, std::char_traits<wchar_t> > const_cwstring;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
/// A cstring of @c char16_t
typedef basic_cstring<char16_t> u16cstring;
/// A cstring of @c char32_t
typedef basic_cstring<char32_t> u32cstring;

/// A cstring of @c const_char16_t
typedef basic_cstring<const char16_t, std::char_traits<char16_t> > const_u16cstring;
/// A cstring of @c const_char32_t
typedef basic_cstring<const char32_t, std::char_traits<char32_t> > const_u32cstring;
#endif

/** @} */

}

#endif