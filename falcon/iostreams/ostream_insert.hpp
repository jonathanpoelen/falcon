#ifndef FALCON_IOSTREAM_OSTREAM_INSERT_HPP
#define FALCON_IOSTREAM_OSTREAM_INSERT_HPP

#include <falcon/iostreams/ostream_fill.hpp>
#include <falcon/iostreams/ostream_write.hpp>

namespace falcon {

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_insert(
  std::basic_ostream<CharT, Traits>& out
, const CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<CharT, Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	typename ostream_type::sentry cerb(out);
	if (cerb)
	{
		const std::streamsize w = out.width();
		if (w > n)
		{
			const bool left
        = ((out.flags() & ios_base::adjustfield) == ios_base::left);
			if (!left)
				ostream_fill(out, w - n);
			if (out.good())
				ostream_write(out, s, n);
			if (left && out.good())
				ostream_fill(out, w - n);
		}
		else
			ostream_write(out, s, n);
		out.width(0);
	}
	return out;
}

template<class CharT, class Traits, class Alloc>
std::basic_ostream<CharT, Traits>&
ostream_insert(
  std::basic_ostream<CharT, Traits>& out
, const std::basic_string<CharT, Traits, Alloc>& s)
{ return ostream_insert(out, s.data(), s.size()); }

}

#endif
