#ifndef FALCON_ISTREAM_OPERATORS_HPP
#define FALCON_ISTREAM_OPERATORS_HPP

#include <iosfwd>

template <typename _CharT, typename _Trait, std::size_t _N>
std::basic_istream<_CharT, _Trait>&
operator>>(std::basic_istream<_CharT, _Trait>& __in, _CharT (&__s)[_N])
{ return __in.read(__s, _N); }

template <typename _CharT, typename _Trait, typename _T, std::size_t _N>
std::basic_istream<_CharT, _Trait>&
operator>>(std::basic_istream<_CharT, _Trait>& __in, _T (&__v)[_N])
{
	std::size_t __n = 0;
	while (__n++ != _N && (__in >> __v))
		;
	return __in;
}

#endif