#ifndef FALCON_IOSTREAMS_GET_FILE_CONTENTS_HPP
#define FALCON_IOSTREAMS_GET_FILE_CONTENTS_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/system_error.hpp>
#include <falcon/iostreams/copy.hpp>

#include <fstream>
#include <string>
#include <cerrno>

namespace falcon {
namespace iostreams {

/**
 * \return errno or 0
 */
template<class String>
int get_file_contents(String& s, const char * name)
{
  typedef typename String::value_type char_type;
  typedef typename String::traits_type traits_type;

  std::basic_filebuf<char_type, traits_type> buf;

  char_type c;
  buf.pubsetbuf(&c, 1);

  if (!buf.open(name, std::ios::in)) {
    return errno;
  }

  const std::streamsize sz = buf.in_avail();
  if (sz == std::streamsize(-1)) {
    return errno;
  }

#if __cplusplus >= 201103L
  s.resize(std::size_t(sz));
  const std::streamsize n = buf.sgetn(&s[0], std::streamsize(s.size()));
  return (sz != n) ? s.resize(std::size_t(n)), errno : 0;
#else
  s.reserve(std::size_t(sz));
  char_type * cs = new char_type[sz];
  const std::streamsize n = buf.sgetn(cs, sz);
  const int err = (sz != n) ? errno : 0;
  s.assign(cs, std::size_t(n));
  delete[] cs;
  return err;
#endif
}

/**
 * \param[out] err  set to errno or 0
 * @{
 */
template<class String>
String get_file_contents(const char * name, int * err)
{
  String s;
  const int ret = get_file_contents(s, name);
  if (err) {
    *err = ret;
  }
  return s;
}

std::string
get_file_contents(const char * name, int * err)
{ return get_file_contents<std::string>(name, err); }

std::wstring
get_wfile_contents(const char * name, int * err)
{ return get_file_contents<std::wstring>(name, err); }
//@}

/**
 * \exception system_error
 * @{
 */
template<class String>
String get_file_contents(const char * name)
{
  String s;
  const int ret = get_file_contents(s, name);
  if (ret) {
    throw system_error(error_code(ret, system_category()));
  }
  return s;
}

std::string
get_file_contents(const char * name)
{ return get_file_contents<std::string>(name); }

std::wstring
get_wfile_contents(const char * name)
{ return get_file_contents<std::wstring>(name); }
//@}

template<class CharT>
std::streamsize
get_file_contents(const char * name, const CharT * s, std::streamsize n)
{
  errno = 0;
  if (n) {
    std::basic_filebuf<CharT> sbin;
    CharT c;
    sbin.pubsetbuf(&c, 1);
    if (sbin.open(name, std::ios_base::in)) {
      return sbin.sgetn(s, n);
    }
  }
  return 0;
}

template<class CharT, class Traits>
std::ios_base::iostate
get_file_contents(
  const char * name
, std::basic_streambuf<CharT, Traits> * sbout)
{
  std::ios_base::iostate ret = std::ios_base::goodbit;
  if (sbout) {
    std::basic_filebuf<CharT> sbin;
    CharT c;
    sbin.pubsetbuf(&c, 1);
    ret = sbin.open(name, std::ios_base::in)
    ? aux_::copy_streambuf(*sbin, *sbout)
    : std::ios_base::failbit;
  }
  else {
    ret = std::ios_base::failbit;
  }
  return ret;
}

template<  class CharT, class Traits>
std::ios_base::iostate
get_file_contents(
  const char * name
, std::basic_ostream<CharT, Traits>& out)
{ return get_file_contents(name, out.rdbuf()); }


template<class String>
int get_file_contents(String& s, std::string const & name)
{ return get_file_contents(s, name.c_str()); }

template<class String>
String get_file_contents(
  std::string const & name
, int * err)
{ return get_file_contents(name.c_str(), err); }

template<class String>
String get_file_contents(
  std::string const & name)
{ return get_file_contents(name.c_str()); }

std::string
get_file_contents(std::string const & name, int * err)
{ return get_file_contents<std::string>(name.c_str(), err); }

std::string
get_file_contents(
  std::string const & name)
{ return get_file_contents<std::string>(name.c_str()); }

std::wstring
get_wfile_contents(std::string const & name, int * err)
{ return get_file_contents<std::wstring>(name.c_str(), err); }

std::wstring
get_wfile_contents(std::string const & name)
{ return get_file_contents<std::wstring>(name.c_str()); }

template<class CharT>
std::streamsize
get_file_contents(
  std::string const & name
, const CharT * s
, std::streamsize n)
{ return get_file_contents(name.c_str(), s, n); }

template<class CharT, class Traits>
std::ios_base::iostate
get_file_contents(
  std::string const & name
, std::basic_streambuf<CharT, Traits> * sbout)
{ return get_file_contents(name.c_str(), sbout); }

template<class CharT, class Traits>
std::ios_base::iostate
get_file_contents(
  std::string const & name
, std::basic_ostream<CharT, Traits>& out)
{ return get_file_contents(name.c_str(), out.rdbuf()); }

}
}

#endif
