#ifndef FALCON_IOSTREAM_OPERATORS_HPP
#define FALCON_IOSTREAM_OPERATORS_HPP

#include <iosfwd>

template <class CharT, class Traits, std::size_t _N>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& in, CharT (&s)[_N])
{ return in.read(s, _N); }

template <class CharT, class Traits, class _T, std::size_t _N>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& in, _T (&v)[_N])
{
	std::size_t n = 0;
	while (n++ != _N && (in >> v))
		;
	return in;
}

#endif
