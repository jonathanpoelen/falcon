#ifndef FALCON_IOSTREAMS_GET_CONTENTS_FILE_HPP
#define FALCON_IOSTREAMS_GET_CONTENTS_FILE_HPP

#include <fstream>

namespace falcon {


template<typename String>
void __get_contents_file(String& s, const char * name, bool * err = 0)
{
  if (err)
    *err = false;

  typedef typename String::value_type char_type;
  typedef typename String::traits_type traits_type;

  std::basic_filebuf<char_type, traits_type> buf;

  if (buf.open(name, std::ios::in)) {

# ifdef __GNUC__
    const std::streamsize sz = buf.in_avail() + 1;
    if (sz == 1) {
      if (err) {
        *err = true;
      }
      s.clear();
      return ;
    }
# endif

#if __cplusplus >= 201103L
# ifdef __GNUC__
    s.resize(sz);
    buf.close();
    buf.pubsetbuf(&s[0], s.size());
    if (!buf.open(name, std::ios::in)) {
      return ;
    }
    if (traits_type::eq_int_type(buf.sgetc(), traits_type::eof())) {
      return ;
    }
    if (err)
      *err = true;
    s.pop_back();
# else
    s.resize(buf.in_avail());
    const std::streamsize n = buf.sgetn(&s[0], s.size());
# endif
#else
# ifdef __GNUC__
    const std::streamsize sz = buf.in_avail() + 1;
    char_type * cs = new char_type[sz];
    buf.close();
    buf.pubsetbuf(cs, sz);
    if (!buf.open(name, std::ios::in)) {
      return ;
    }
    if (traits_type::eq_int_type(buf.sgetc(), traits_type::eof())) {
      return ;
    }
    if (err)
      *err = true;
    s.assign(cs, sz - 1);
    delete[] cs;
# else
    const std::streamsize sz = buf.in_avail();
    char_type * cs = new char_type[sz];
    const std::streamsize n = buf.sgetn(cs, sz);
    s.assign(cs, sz);
    delete[] cs;
# endif
#endif

#ifndef __GNUC__
    if (err && n == static_cast<std::streamsize>(s.size()))
      *err = true;
#endif
  }
}

template<typename String>
String
__get_contents_file(const char * name, bool * err = 0)
{
  String s;
  __get_contents_file(s, name, err);
  return s;
}

#if __cplusplus >= 201103L
template<typename String>
String&
get_contents_file(String& s, const char * name, bool * err = 0)
{
  s.clear();
  __get_contents_file(s, name, err);
  return s;
}
#endif

template<typename String>
String
get_basic_contents_file(const char * name, bool * err = 0)
{ return __get_contents_file<String>(name, err); }

std::string
get_contents_file(const char * name, bool * err = 0)
{ return __get_contents_file<std::string>(name, err); }

std::wstring
get_wcontents_file(const char * name, bool * err = 0)
{ return __get_contents_file<std::wstring>(name, err); }

template<typename CharT>
std::streamsize
get_contents_file(const char * name, const CharT * s, std::streamsize n,
                  bool * err = 0)
{
  if (err)
    *err = true;
  if (n)
  {
    std::basic_filebuf<CharT> sbin;
    if (sbin.open(name, std::ios_base::in))
      return sbin.sgetn(s, n);
    if (err)
      *err = false;
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
      return true;
    }
  }
  return false;
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
      return true;
    }
  }
  return false;
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
