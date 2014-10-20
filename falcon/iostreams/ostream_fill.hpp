#ifndef FALCON_IOSTREAM_OSTREAM_FILL_HPP
#define FALCON_IOSTREAM_OSTREAM_FILL_HPP

#include <iosfwd>

namespace falcon {

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_fill(std::basic_ostream<CharT, Traits>& out, std::streamsize n, CharT c)
{
	typedef std::basic_ostream<CharT, Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

  for (std::streamsize i = 0; i < n; ++i)
	{
		if (Traits::eq_int_type(out.rdbuf()->sputc(c), Traits::eof()))
		{
			out.setstate(ios_base::badbit);
			break;
		}
	}

	return out;
}

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_fill(std::basic_ostream<CharT, Traits>& out, std::streamsize n)
{ return ostream_fill(out, n, out.fill()); }

}

#endif
