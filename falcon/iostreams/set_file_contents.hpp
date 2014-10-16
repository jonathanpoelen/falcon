#ifndef FALCON_IOSTREAM_SET_FILE_CONTENTS_HPP
#define FALCON_IOSTREAM_SET_FILE_CONTENTS_HPP

#include <falcon/iostreams/copy.hpp>

#include <fstream> //basic_streambuf

#if __cplusplus >= 201103L
#define FALCON_CHECK_CHAR_TYPE() \
  static_assert(std::is_same<CharT, class String::value_type>(),\
                "Incompatible CharT")
#endif

namespace falcon {
namespace iostreams {

template<class CharT>
std::streamsize
set_file_contents(
  const char * name
, const CharT * s
, std::size_t size)
{
  if (size)
  {
    std::basic_filebuf<CharT> sbout;
    CharT c;
    sbout.pubsetbuf(&c, 1);
    if (sbout.open(name, std::ios_base::out)) {
      return sbout.sputn(s, size);
    }
  }
  return 0;
}

template<class CharT>
std::streamsize
set_file_contents(const char * name, const CharT * s)
{
  if (*s)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out)) {
      std::size_t len = std::char_traits<CharT>::length(s);
      // TODO len > std::streamsize::max()
      return sbout.sputn(s, std::streamsize(len));
    }
  }
  return 0;
}

template<class CharT, class String>
std::streamsize
set_file_contents(const char * name, String& s, std::size_t size)
{
  FALCON_CHECK_CHAR_TYPE();
  if (size)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out)) {
      return sbout.sputn(s.data(), size);
    }
  }
  return 0;
}

template<class CharT, class String>
std::streamsize
set_file_contents(const char * name, String& s)
{
  FALCON_CHECK_CHAR_TYPE();
  if (*s)
  {
    std::basic_filebuf<CharT> sbout;
    if (sbout.open(name, std::ios_base::out)) {
      return sbout.sputn(s.data(), s.size());
    }
  }
  return 0;
}

template<class CharT, class Traits>
std::streamsize
set_file_contents(
  const char * name
, std::basic_streambuf<CharT, Traits> * sbin)
{
  if (sbin)
  {
    std::basic_filebuf<CharT, Traits> sbout;
    if (sbout.open(name, std::ios_base::out)) {
      return copy(&sbout, sbin);
    }
  }
  return std::streamsize(-1);
}

template<class CharT, class Traits>
std::streamsize
set_file_contents(
  const char * name
, std::basic_istream<CharT, Traits>& is)
{ return set_file_contents(name, is.rdbuf()); }


template<class CharT>
std::streamsize
set_file_contents(
  const std::string & name
, const CharT * s
, std::size_t size)
{ return set_file_contents(name.c_str(), s, size); }

template<class CharT>
std::streamsize
set_file_contents(const std::string & name, const CharT * s)
{ return set_file_contents(name.c_str(), s); }

template<class CharT, class String>
std::streamsize
set_file_contents(const std::string & name, String& s, std::size_t size)
{ return set_file_contents(name.c_str(), s, size); }

template<class CharT, class String>
std::streamsize
set_file_contents(const std::string & name, String& s)
{ return set_file_contents(name.c_str(), s); }

template<class CharT, class Traits>
std::streamsize
set_file_contents(
  const std::string & name
, std::basic_streambuf<CharT, Traits> * sbin)
{ return set_file_contents(name.c_str(), sbin); }

template<class CharT, class Traits>
std::streamsize
set_file_contents(
  const std::string & name
, std::basic_istream<CharT, Traits>& is)
{ return set_file_contents(name.c_str(), is.rdbuf()); }

}
}

#endif
