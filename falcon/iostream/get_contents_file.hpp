#ifndef FALCON_IOSTREAM_GET_CONTENTS_FILE_HPP
#define FALCON_IOSTREAM_GET_CONTENTS_FILE_HPP

#include <fstream>
#include <sstream>
#include <falcon/iostream/set_contents_file.hpp>

namespace falcon {

template<typename _CharT>
std::basic_string<_CharT>
__get_contents_file(const char * __name, std::ios_base::iostate * __err = 0)
{
  if (__err)
    *__err = std::ios_base::failbit;
  std::basic_filebuf<_CharT> __sbin;
  if (__sbin.open(__name, std::ios_base::in))
  {
    std::basic_ostringstream<_CharT> oss;
    std::ios_base::iostate __tmp = __set_contents_file(*oss.rdbuf(), &__sbin);
    if (__err)
      *__err = __tmp;
    return oss.str();
  }
  return std::basic_string<_CharT>();
}

std::string
get_contents_file(const char * __name, std::ios_base::iostate * __err = 0)
{ return __get_contents_file<char>(__name, __err); }

std::wstring
get_wcontents_file(const char * __name, std::ios_base::iostate * __err = 0)
{ return __get_contents_file<wchar_t>(__name, __err); }

template<typename _CharT>
std::streamsize
get_contents_file(const char * __name, const _CharT * __s, std::streamsize __n,
                  std::ios_base::iostate * __err = 0)
{
	if (__err)
      *__err = std::ios_base::goodbit;
	if (__n)
	{
      std::basic_filebuf<_CharT> __sbin;
      if (__sbin.open(__name, std::ios_base::in))
        return __sbin.sgetn(__s, __n);
      if (__err)
        *__err = std::ios_base::failbit;
	}
	return 0;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
get_contents_file(const char * __name, std::basic_streambuf<_CharT, _Traits> * __sbout)
{
  if (__sbout)
  {
    std::basic_filebuf<_CharT> __sbin;
    if (__sbin.open(__name, std::ios_base::in))
      return __set_contents_file(*__sbout, &__sbin);
  }
  return std::ios_base::failbit;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
get_contents_file(const char * __name, std::basic_ostream<_CharT, _Traits>& __out)
{
  if (!__out.rdbuf())
  {
    std::basic_filebuf<_CharT> __sbin;
    if (__sbin.open(__name, std::ios_base::in))
        return __set_contents_file(__out.rdbuf(), &__sbin);
  }
  return std::ios_base::failbit;
}

template<typename _CharT, typename _Traits>
std::streamsize
get_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbin,
                  const _CharT * __s, std::streamsize __n)
{
  return __n && __sbin
  ? __sbin->sgetn(__s, __n)
  : 0;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
get_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbin,
                  std::basic_streambuf<_CharT, _Traits> * __sbout)
{ return set_contents_file(__sbout, __sbin); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
get_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbin,
                  std::basic_ostream<_CharT, _Traits>& __out)
{ return set_contents_file(__sbin, __out); }

template<typename _CharT, typename _Traits>
std::streamsize
get_contents_file(std::basic_istream<_CharT, _Traits>& __in,
                  const _CharT * __s, std::streamsize __n)
{ return __in.read(__s, __n); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
get_contents_file(std::basic_istream<_CharT, _Traits>& __in,
                  std::basic_streambuf<_CharT, _Traits> * __sbout)
{
  __in >> __sbout;
  return __in.state();
}

template<typename _CharT, typename _Traits>
std::streamsize
get_contents_file(std::basic_istream<_CharT, _Traits>& __in,
                  std::basic_ostream<_CharT, _Traits>& __out)
{
  __in >> __out.rdbuf();
  return __in.state();
}

}

#endif
