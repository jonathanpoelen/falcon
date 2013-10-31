#ifndef FALCON_STRING_CSTRINGFW_HPP
#define FALCON_STRING_CSTRINGFW_HPP

#include <iosfwd>
#include <string>

// namespace std {
//   template<typename>
//   class char_traits;
//
//   template<typename,typename,typename>
//   class basic_string;
// }

namespace falcon {

template<typename CharT>
struct cstring_allocator
{
  template<typename T>
  struct rebind
  { typedef cstring_allocator<T> other; };
};

template<typename CharT>
struct cstring_allocator<const CharT>
{
  template<typename T>
  struct rebind
  { typedef cstring_allocator<const T> other; };
};

template<typename CharT, typename Traits>
struct __cstring
{ typedef std::basic_string<CharT, Traits, cstring_allocator<CharT> > __type; };

template<typename CharT, typename Traits>
struct __cstring<const CharT, Traits>
{ typedef std::basic_string<CharT, Traits, cstring_allocator<const CharT> > __type; };

template<typename CharT>
struct __cstring<const CharT, std::char_traits<const CharT> >
{ typedef std::basic_string<CharT, std::char_traits<CharT>, cstring_allocator<const CharT> > __type; };

/**
 * @defgroup strings Strings
 *
 * @{
 */

#if __cplusplus >= 201103L
template < typename CharT, typename Traits = std::char_traits<CharT> >
using basic_cstring = typename __cstring<CharT, Traits>::__type;

template< typename CharT, typename Traits = std::char_traits<CharT> >
using basic_const_cstring = typename __cstring<const CharT, Traits>::__type;
#endif

/// A cstring of @c char
typedef std::basic_string<char, std::char_traits<char>, cstring_allocator<char> > cstring;
/// A cstring of @c wchar_t
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, cstring_allocator<wchar_t> > cwstring;

/// A cstring of @c const_char
typedef std::basic_string<char, std::char_traits<char>, cstring_allocator<const char> > const_cstring;
/// A cstring of @c const_wchar_t
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, cstring_allocator<const wchar_t> > const_cwstring;

#if __cplusplus >= 201103L
/// A cstring of @c char16_t
typedef std::basic_string<char16_t, std::char_traits<char16_t>, cstring_allocator<char16_t> > u16cstring;
/// A cstring of @c char32_t
typedef std::basic_string<char32_t, std::char_traits<char32_t>, cstring_allocator<char32_t> > u32cstring;

/// A cstring of @c const_char16_t
typedef std::basic_string<char16_t, std::char_traits<char16_t>, cstring_allocator<const char16_t> > const_u16cstring;
/// A cstring of @c const_char32_t
typedef std::basic_string<char32_t, std::char_traits<char32_t>, cstring_allocator<const char32_t> > const_u32cstring;
#endif

/** @} */

}

#endif
