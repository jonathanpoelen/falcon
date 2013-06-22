#ifndef FALCON_IOSTREAM_GET_CONTENTS_FILE_HPP
#define FALCON_IOSTREAM_GET_CONTENTS_FILE_HPP

#include <falcon/iostream/set_contents_file.hpp>

#include <fstream>

#ifndef FALCON_NO_BOOST_FILESYSTEM
#include <boost/filesystem/operations.hpp>
#else
#include <sstream>
#endif

namespace falcon {


#ifndef FALCON_NO_BOOST_FILESYSTEM
template<typename String>
void __get_contents_file(String& s, const char * name, std::ios_base::iostate * err = 0)
{
  if (err)
    *err = std::ios_base::failbit;

  typedef typename String::value_type char_type;

  boost::system::error_code ec;
  uintmax_t size = boost::filesystem::file_size(name, ec);
  if (!ec) {
    s.reserve(static_cast<size_t>(size)+1);
    std::basic_filebuf<char_type> sbin;
    if (sbin.open(name, std::ios_base::in)) {
      char_type* data = const_cast<char_type*>(s.data());
      std::streamsize ssize = sbin.sgetn(data, static_cast<typename std::streamsize>(size));
      *(data + ssize) = 0;
      if (err)
        *err = std::ios_base::goodbit;
    }
  }
}
#endif

template<typename String>
String
__get_contents_file(const char * name, std::ios_base::iostate * err = 0)
{
#ifndef FALCON_NO_BOOST_FILESYSTEM
  String s;
  __get_contents_file<>(s, name, err);
  return s;
#else
  typedef typename String::value_type char_type;
  typedef std::basic_filebuf<char_type> filebuf;
  if (err)
    *err = std::ios_base::failbit;
  filebuf sbin;
  if (sbin.open(name, std::ios_base::in))
  {
    std::basic_ostringstream<char_type> oss;
    __set_contents_file(oss.rdbuf(), &sbin);
    if (err)
      *err = std::ios_base::goodbit;
    return oss.str();
  }
  return String();
#endif
}

#if __cplusplus >= 201103L
template<typename String>
String&
get_contents_file(String& s, const char * name, std::ios_base::iostate * err = 0)
{
  s.clear();
  __get_contents_file<>(s, name, err);
  return s;
}
#endif

template<typename String>
String
get_basic_contents_file(const char * name, std::ios_base::iostate * err = 0)
{ return __get_contents_file<String>(name, err); }

std::string
get_contents_file(const char * name, std::ios_base::iostate * err = 0)
{ return __get_contents_file<std::string>(name, err); }

std::wstring
get_wcontents_file(const char * name, std::ios_base::iostate * err = 0)
{ return __get_contents_file<std::wstring>(name, err); }

template<typename CharT>
std::streamsize
get_contents_file(const char * name, const CharT * s, std::streamsize n,
                  std::ios_base::iostate * err = 0)
{
  if (err)
    *err = std::ios_base::goodbit;
  if (n)
  {
    std::basic_filebuf<CharT> sbin;
    if (sbin.open(name, std::ios_base::in))
      return sbin.sgetn(s, n);
    if (err)
      *err = std::ios_base::failbit;
  }
  return 0;
}

template<typename CharT, typename Traits>
std::ios_base::iostate
get_contents_file(const char * name, std::basic_streambuf<CharT, Traits> * sbout)
{
  if (sbout)
  {
    std::basic_filebuf<CharT> sbin;
    if (sbin.open(name, std::ios_base::in)) {
      __set_contents_file(sbout, &sbin);
      return std::ios_base::goodbit;
    }
  }
  return std::ios_base::failbit;
}

template<typename CharT, typename Traits>
std::ios_base::iostate
get_contents_file(const char * name, std::basic_ostream<CharT, Traits>& out)
{
  if (!out.rdbuf())
  {
    std::basic_filebuf<CharT> sbin;
    if (sbin.open(name, std::ios_base::in)){
      return __set_contents_file(out.rdbuf(), &sbin);
      return std::ios_base::goodbit;
    }
  }
  return std::ios_base::failbit;
}

template<typename CharT, typename Traits>
std::streamsize
get_contents_file(std::basic_streambuf<CharT, Traits> * sbin,
                  const CharT * s, std::streamsize n)
{
  return n && sbin
  ? sbin->sgetn(s, n)
  : 0;
}

template<typename CharT, typename Traits>
std::ios_base::iostate
get_contents_file(std::basic_streambuf<CharT, Traits> * sbin,
                  std::basic_streambuf<CharT, Traits> * sbout)
{ return set_contents_file(sbout, sbin); }

template<typename CharT, typename Traits>
std::ios_base::iostate
get_contents_file(std::basic_streambuf<CharT, Traits> * sbin,
                  std::basic_ostream<CharT, Traits>& out)
{ return set_contents_file(sbin, out); }

template<typename CharT, typename Traits>
std::streamsize
get_contents_file(std::basic_istream<CharT, Traits>& in,
                  const CharT * s, std::streamsize n)
{ return in.read(s, n); }

template<typename CharT, typename Traits>
std::ios_base::iostate
get_contents_file(std::basic_istream<CharT, Traits>& in,
                  std::basic_streambuf<CharT, Traits> * sbout)
{
  in >> sbout;
  return in.state();
}

template<typename CharT, typename Traits>
std::streamsize
get_contents_file(std::basic_istream<CharT, Traits>& in,
                  std::basic_ostream<CharT, Traits>& out)
{
  in >> out.rdbuf();
  return in.state();
}

}

#endif
