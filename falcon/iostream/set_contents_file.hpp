#ifndef FALCON_IOSTREAM_SET_CONTENTS_FILE_HPP
#define FALCON_IOSTREAM_SET_CONTENTS_FILE_HPP

#include <fstream> //basic_streambuf

#if __cplusplus >= 201103L
#define FALCON_CHECK_CHAR_TYPE \
  static_assert(std::is_same<CharT, typename String::value_type>(),\
                "Incompatible CharT");
#endif

namespace falcon {

template<typename String, typename CharT, typename Traits>
std::streamsize
__set_contents_file(std::basic_streambuf<CharT, Traits>& sbout,
                    String s, std::size_t size)
{
  typedef typename std::basic_streambuf<CharT, Traits>::int_type int_type;
  std::size_t n = 0;
  int_type c;
  do {
    c = sbout.sputc(Traits::to_char_type(s[n]));
  } while (!Traits::eq_int_type(c, Traits::eof()) && ++n != size);
  return std::streamsize(n);
}

template<typename String, typename CharT, typename Traits>
std::streamsize
__set_contents_file(std::basic_streambuf<CharT, Traits>& sbout, String s)
{
  typedef typename std::basic_streambuf<CharT, Traits>::int_type int_type;
  std::size_t n = 0;
  int_type c;
  do {
    c = sbout.sputc(Traits::to_char_type(s[n]));
  } while (!Traits::eq_int_type(c, Traits::eof()) && s[++n]);
  return std::streamsize(n);
}

template<typename CharT, typename Traits>
std::streamsize
__set_contents_file(std::basic_streambuf<CharT, Traits> * sbout,
                    std::basic_streambuf<CharT, Traits> * sbin)
{
  typedef typename std::basic_streambuf<CharT, Traits>::int_type int_type;
  std::size_t n = 0;
  int_type c = sbin->sgetc();
  while (!Traits::eq_int_type(c, Traits::eof())) {
    c = sbout->sputc(Traits::to_char_type(c));
    if (Traits::eq_int_type(c, Traits::eof())) {
        break;
    }
    ++n;
    c = sbin->snextc();
  }
  return std::streamsize(n);
}

template<typename CharT>
std::streamsize
set_contents_file(const char * name, const CharT * s, std::size_t size)
{
  if (size)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out))
      return __set_contents_file<const CharT *>(sbout, s, size);
  }
  return std::streamsize(-1);
}

template<typename CharT>
std::streamsize
set_contents_file(const char * name, const CharT * s)
{
  if (*s)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out))
      return __set_contents_file<const CharT *>(sbout, s);
  }
  return std::streamsize(-1);
}

template<typename CharT, typename String>
std::streamsize
set_contents_file(const char * name, String& s, std::size_t size)
{
  FALCON_CHECK_CHAR_TYPE
  if (size)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out))
      return __set_contents_file<String&>(sbout, s, size);
  }
  return std::streamsize(-1);
}

template<typename CharT, typename String>
std::streamsize
set_contents_file(const char * name, String& s)
{
  FALCON_CHECK_CHAR_TYPE
  if (*s)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out))
      return __set_contents_file<String&>(sbout, s);
  }
  return std::streamsize(-1);
}

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(const char * name, std::basic_streambuf<CharT, Traits> * sbin)
{
  if (sbin)
  {
    std::basic_filebuf<CharT, Traits> sbout;
    if (sbout.open(name, std::ios_base::out))
      return __set_contents_file(&sbout, sbin);
  }
  return std::streamsize(-1);
}

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(const char * name, std::basic_istream<CharT, Traits>& is)
{ return set_contents_file(name, is.rdbuf()); }

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_streambuf<CharT, Traits> * sbout,
                  const CharT * s, std::size_t size)
{
  return !size || !sbout
  ? std::streamsize(-1)
  : __set_contents_file<const CharT *>(*sbout, s, size);
}

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_streambuf<CharT, Traits> * sbout, const CharT * s)
{
  return !sbout
  ? std::streamsize(-1)
  : __set_contents_file<const CharT *>(*sbout, s);
}

template<typename CharT, typename Traits, typename String>
std::streamsize
set_contents_file(std::basic_streambuf<CharT, Traits> * sbout,
                  String& s, std::size_t size)
{
  FALCON_CHECK_CHAR_TYPE
  return !size || !sbout
  ? std::streamsize(-1)
  : __set_contents_file<String&>(*sbout, s, size);
}

template<typename CharT, typename Traits, typename String>
std::streamsize
set_contents_file(std::basic_streambuf<CharT, Traits> * sbout, String& s)
{
  FALCON_CHECK_CHAR_TYPE
  return !sbout
  ? std::streamsize(-1)
  : __set_contents_file<String&>(*sbout, s);
}

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_streambuf<CharT, Traits> * sbout,
                  std::basic_streambuf<CharT, Traits> * sbin)
{
  return !sbout || !sbin
  ? std::streamsize(-1)
  : __set_contents_file(sbout, sbin);
}

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_streambuf<CharT, Traits> * sbout,
                  std::basic_istream<CharT, Traits>& is)
{ return set_contents_file(sbout, is.rdbuf()); }

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_ostream<CharT, Traits>& __out,
                  const CharT * s, std::size_t size)
{ return set_contents_file(__out.rdbuf(), s, size); }

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_ostream<CharT, Traits>& __out, const CharT * __s)
{ return set_contents_file(__out.rdbuf(), __s); }

template<typename CharT, typename Traits, typename String>
std::streamsize
set_contents_file(std::basic_ostream<CharT, Traits>& __out, String& __s)
{ return set_contents_file(__out.rdbuf(), __s); }

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_ostream<CharT, Traits>& __out,
                  std::basic_streambuf<CharT, Traits> * sbin)
{ return set_contents_file(__out.rdbuf(), sbin); }

template<typename CharT, typename Traits>
std::streamsize
set_contents_file(std::basic_ostream<CharT, Traits>& __out,
                  std::basic_istream<CharT, Traits>& is)
{ return set_contents_file(__out.rdbuf(), is.rdbuf()); }

}

#endif
