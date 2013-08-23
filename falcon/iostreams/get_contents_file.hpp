#ifndef FALCON_IOSTREAMS_GET_CONTENTS_FILE_HPP
#define FALCON_IOSTREAMS_GET_CONTENTS_FILE_HPP

#include <fstream>

namespace falcon {


template<typename String>
void __get_contents_file(String& s, const char * name, std::ios_base::iostate * err = 0)
{
  if (err)
    *err = std::ios_base::failbit;

  typedef typename String::value_type char_type;
  typedef typename String::traits_type traits_type;

  std::basic_filebuf<char_type, traits_type> buf;

  if (buf.open(name, std::ios::in)) {
#if __cplusplus >= 201103L
    s.resize(buf.in_avail());
    const std::streamsize n = buf.sgetn(&s[0], s.size());
#else
    const std::streamsize sz = buf.in_avail();
    char_type * cs = new char_type[sz];
    const std::streamsize n = buf.sgetn(cs, sz);
    s.assign(cs, sz);
    delete[] cs;
#endif
    if (err && n == static_cast<std::streamsize>(s.size()))
      *err = std::ios_base::goodbit;
  }
}

template<typename String>
String
__get_contents_file(const char * name, std::ios_base::iostate * err = 0)
{
  String s;
  __get_contents_file<>(s, name, err);
  return s;
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
