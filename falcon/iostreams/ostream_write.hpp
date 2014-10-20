#ifndef FALCON_IOSTREAM_OSTREAM_WRITE_HPP
#define FALCON_IOSTREAM_OSTREAM_WRITE_HPP

#include <iosfwd>

namespace falcon {

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_write(
  std::basic_ostream<CharT, Traits>& out
, const CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<CharT, Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	if (out.rdbuf()->sputn(s, n) != n)
		out.setstate(ios_base::badbit);

	return out;
}

template<class CharT, class Traits, class Alloc>
std::basic_ostream<CharT, Traits>&
ostream_write(
  std::basic_ostream<CharT, Traits>& out
, const std::basic_string<CharT, Traits, Alloc>& s)
{ return ostream_write(out, s.data(), s.size()); }

}

#endif
