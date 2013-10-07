#ifndef FALCON_STRING_CSTRINGFW_HPP
#define FALCON_STRING_CSTRINGFW_HPP

namespace std {
  template<typename>
  class char_traits;
}

namespace falcon {

template<typename T>
struct __cs_remove_const
{ typedef T type; };

template<typename T>
struct __cs_remove_const<const T>
{ typedef T type; };

/**
 * @defgroup strings Strings
 *
 * @{
 */

template < typename CharT
         , typename Traits = std::char_traits<typename __cs_remove_const<CharT>::type> >
class basic_cstring;

#if __cplusplus >= 201103L
template< typename CharT
        , typename Traits = std::char_traits<typename __cs_remove_const<CharT>::type> >
using basic_const_cstring = basic_cstring<const CharT, Traits>;
#endif

/// A cstring of @c char
typedef basic_cstring<char> cstring;
/// A cstring of @c wchar_t
typedef basic_cstring<wchar_t> cwstring;

/// A cstring of @c const_char
typedef basic_cstring<const char> const_cstring;
/// A cstring of @c const_wchar_t
typedef basic_cstring<const wchar_t> const_cwstring;

#if __cplusplus >= 201103L
/// A cstring of @c char16_t
typedef basic_cstring<char16_t> u16cstring;
/// A cstring of @c char32_t
typedef basic_cstring<char32_t> u32cstring;

/// A cstring of @c const_char16_t
typedef basic_cstring<const char16_t> const_u16cstring;
/// A cstring of @c const_char32_t
typedef basic_cstring<const char32_t> const_u32cstring;
#endif

/** @} */

}

#endif
