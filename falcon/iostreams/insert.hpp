#ifndef FALCON_IOSTREAM_INSERT_HPP
#define FALCON_IOSTREAM_INSERT_HPP

#include <ios>
#include <string>

namespace falcon {

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_write(std::basic_ostream<CharT, Traits>& out,
							const CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<CharT, Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	if (out.rdbuf()->sputn(s, n) != n)
		out.setstate(ios_base::badbit);

	return out;
}

template<class CharT, class Traits, std::size_t N>
std::basic_ostream<CharT, Traits>&
ostream_write(std::basic_ostream<CharT, Traits>& out,
							const CharT (&s)[N])
{ return ostream_write(out, s, static_cast<std::streamsize>(N)); }

template<class CharT, class Traits, class Alloc>
std::basic_ostream<CharT, Traits>&
ostream_write(std::basic_ostream<CharT, Traits>& out,
							const std::basic_string<CharT, Traits, Alloc>& s)
{ return ostream_write(out, s.data(), s.size()); }

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_fill(std::basic_ostream<CharT, Traits>& out, std::streamsize n, CharT c)
{
	typedef std::basic_ostream<CharT, Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

  for (std::streamsize i = 0; i < n; --i)
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

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
ostream_insert(std::basic_ostream<CharT, Traits>& out,
							 const CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<CharT, Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	class ostream_type::sentry cerb(out);
	if (cerb)
	{
		const std::streamsize w = out.width();
		if (w > n)
		{
			const bool left = ((out.flags() & ios_base::adjustfield) == ios_base::left);
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

template<class CharT, class Traits, std::size_t N>
std::basic_ostream<CharT, Traits>&
ostream_insert(std::basic_ostream<CharT, Traits>& out, const CharT(&s)[N])
{ return ostream_insert(out, s, static_cast<std::streamsize>(N)); }

template<class CharT, class Traits, class Alloc>
std::basic_ostream<CharT, Traits>&
ostream_insert(std::basic_ostream<CharT, Traits>& out,
               const std::basic_string<CharT, Traits, Alloc>& s)
{ return ostream_insert(out, s.data(), s.size()); }

}

#endif
