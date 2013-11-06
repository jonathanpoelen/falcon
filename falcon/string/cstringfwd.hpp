#ifndef FALCON_STRING_CSTRINGFW_HPP
#define FALCON_STRING_CSTRINGFW_HPP

#include <string>

namespace falcon {

template<typename CharT>
struct cstring_allocator
{
public:
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef CharT *         pointer;
  typedef const CharT *   const_pointer;
  typedef CharT &         reference;
  typedef const CharT &   const_reference;
  typedef CharT           value_type;

  template<typename T>
  struct rebind
  { typedef cstring_allocator<T> other; };
};

template<typename CharT>
struct cstring_allocator<const CharT>
{
public:
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef const CharT *   pointer;
  typedef const CharT *   const_pointer;
  typedef const CharT &   reference;
  typedef const CharT &   const_reference;
  typedef const CharT     value_type;

  template<typename T>
  struct rebind
  { typedef cstring_allocator<const T> other; };
};

template<typename T1, typename T2>
inline bool
operator==(const cstring_allocator<T1>&, const cstring_allocator<T2>&)
{ return true; }

template<typename T>
inline bool
operator==(const cstring_allocator<T>&, const cstring_allocator<T>&)
{ return true; }

template<typename T1, typename T2>
inline bool
operator!=(const cstring_allocator<T1>&, const cstring_allocator<T2>&)
{ return false; }

template<typename T>
inline bool
operator!=(const cstring_allocator<T>&, const cstring_allocator<T>&)
{ return false; }


template<typename CharT, typename Traits = std::char_traits<CharT> >
struct build_basic_cstring
{ typedef std::basic_string<CharT, Traits, cstring_allocator<CharT> > type; };

template<typename CharT, typename Traits>
struct build_basic_cstring<const CharT, Traits>
{ typedef std::basic_string<CharT, Traits, cstring_allocator<const CharT> > type; };

template<typename CharT>
struct build_basic_cstring<const CharT, std::char_traits<const CharT> >
{ typedef std::basic_string<CharT, std::char_traits<CharT>, cstring_allocator<const CharT> > type; };

/**
 * @defgroup strings Strings
 *
 * @{
 */

#if __cplusplus >= 201103L
template < typename CharT, typename Traits = std::char_traits<CharT> >
using basic_cstring = typename build_basic_cstring<CharT, Traits>::type;

template< typename CharT, typename Traits = std::char_traits<CharT> >
using basic_const_cstring = typename build_basic_cstring<const CharT, Traits>::type;
#endif

/// A cstring of @c char
typedef typename build_basic_cstring<char           >::type cstring;
/// A cstring of @c wchar_t
typedef typename build_basic_cstring<wchar_t        >::type cwstring;

/// A cstring of @c const_char
typedef typename build_basic_cstring<const char     >::type const_cstring;
/// A cstring of @c const_wchar_t
typedef typename build_basic_cstring<const wchar_t  >::type const_cwstring;

#if __cplusplus >= 201103L
/// A cstring of @c char16_t
typedef typename build_basic_cstring<char16_t       >::type u16cstring;
/// A cstring of @c char32_t
typedef typename build_basic_cstring<char32_t       >::type u32cstring;

/// A cstring of @c const_char16_t
typedef typename build_basic_cstring<const char16_t >::type const_u16cstring;
/// A cstring of @c const_char32_t
typedef typename build_basic_cstring<const char32_t >::type const_u32cstring;
#endif

/** @} */

}

#endif
