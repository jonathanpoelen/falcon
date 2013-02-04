#ifndef FALCON_IOSTREAM_SET_CONTENTS_FILE_HPP
#define FALCON_IOSTREAM_SET_CONTENTS_FILE_HPP

#include <fstream>

namespace falcon {

template<typename _CharT, typename _Traits>
std::ios_base::iostate
__set_contents_file(std::basic_streambuf<_CharT, _Traits>& __sbout,
										const _CharT * __s, std::size_t __size)
{
	std::ios_base::iostate __err = std::ios_base::goodbit;
	std::size_t __n = 0;
	typename std::basic_streambuf<_CharT, _Traits>::int_type __c;
	do
	{
		__c = __sbout.sputc(_Traits::to_char_type(__s[__n]));
		if (_Traits::eq_int_type(__c, _Traits::eof()))
		{
			__err |= std::ios_base::eofbit;
			break;
		}
	} while (++__n != __size);
	return __err;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
__set_contents_file(std::basic_streambuf<_CharT, _Traits>& __sbout,
										const _CharT * __s)
{
	std::ios_base::iostate __err = std::ios_base::goodbit;
	std::size_t __n = 0;
	typename std::basic_streambuf<_CharT, _Traits>::int_type __c;
	do
	{
		__c = __sbout.sputc(_Traits::to_char_type(__s[__n]));
		if (_Traits::eq_int_type(__c, _Traits::eof()))
		{
			__err |= std::ios_base::eofbit;
			break;
		}
	} while (__s[++__n]);
	return __err;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
__set_contents_file(std::basic_streambuf<_CharT, _Traits>& __sbout,
										std::basic_streambuf<_CharT, _Traits> * __sbin)
{
	std::ios_base::iostate __err = std::ios_base::goodbit;
	std::size_t __n = 0;
	typename std::basic_streambuf<_CharT, _Traits>::int_type __c = __sbin->sgetc();
	while (!_Traits::eq_int_type(__c, _Traits::eof()))
	{
		__c = __sbout.sputc(_Traits::to_char_type(__c));
		if (_Traits::eq_int_type(__c, _Traits::eof()))
		{
			__err |= std::ios_base::eofbit;
			break;
		}
		++__n;
		__c = __sbin->snextc();
	}
	if (!__n)
		__err |= std::ios_base::failbit;
	return __err;
}

template<typename _CharT>
std::ios_base::iostate
set_contents_file(const char * __name, const _CharT * __s, std::size_t __size)
{
	std::ios_base::iostate __err = std::ios_base::failbit;
	if (__size)
	{
		std::basic_filebuf<_CharT> __sbout;
		if (__sbout.open(__name, std::ios_base::out))
			__err = __set_contents_file(__sbout, __s, __size);
	}
	return __err;
}

template<typename _CharT>
std::ios_base::iostate
set_contents_file(const char * __name, const _CharT * __s)
{
	std::ios_base::iostate __err = std::ios_base::failbit;
	if (*__s)
	{
		std::basic_filebuf<_CharT> __sbout;
		if (__sbout.open(__name, std::ios_base::out))
			__err = __set_contents_file(__sbout, __s);
	}
	return __err;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(const char * __name,
									std::basic_streambuf<_CharT, _Traits> * __sbin)
{
	std::ios_base::iostate __err = std::ios_base::failbit;
	if (__sbin)
	{
		std::basic_filebuf<_CharT, _Traits> __sbout;
		if (__sbout.open(__name, std::ios_base::out))
			__err = __set_contents_file(__sbout, __sbin);
	}
	return __err;
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(const char * __name,
									std::basic_istream<_CharT, _Traits>& __is)
{ return set_contents_file(__name, __is.rdbuf()); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbout,
									const _CharT * __s, std::size_t __size)
{
	return !__size || !__sbout
	? std::ios_base::failbit
	: __set_contents_file(*__sbout, __s, __size);
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbout,
									const _CharT * __s)
{
	return !__sbout
	? std::ios_base::failbit
	: __set_contents_file(*__sbout, __s);
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbout,
									std::basic_streambuf<_CharT, _Traits> * __sbin)
{
	return !__sbout || !__sbin
	? std::ios_base::failbit
	: __set_contents_file(*__sbout, __sbin);
}

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_streambuf<_CharT, _Traits> * __sbout,
									std::basic_istream<_CharT, _Traits>& __is)
{ return set_contents_file(__sbout, __is.rdbuf()); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_ostream<_CharT, _Traits>& __out,
									const _CharT * __s, std::size_t __size)
{ return set_contents_file(__out.rdbuf(), __s, __size); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_ostream<_CharT, _Traits>& __out,
									const _CharT * __s)
{ return set_contents_file(__out.rdbuf(), __s); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_ostream<_CharT, _Traits>& __out,
									std::basic_streambuf<_CharT, _Traits> * __sbin)
{ return set_contents_file(__out.rdbuf(), __sbin); }

template<typename _CharT, typename _Traits>
std::ios_base::iostate
set_contents_file(std::basic_ostream<_CharT, _Traits>& __out,
									std::basic_istream<_CharT, _Traits>& __is)
{ return set_contents_file(__out.rdbuf(), __is.rdbuf()); }

}

#endif