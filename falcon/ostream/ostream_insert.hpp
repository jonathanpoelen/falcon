#ifndef _FALCON_OSTREAM_OSTREAM_INSERT_HPP
#define _FALCON_OSTREAM_OSTREAM_INSERT_HPP

#include <iosfwd>

namespace falcon {

template<typename _CharT, typename _Traits>
inline void ostream_write(std::basic_ostream<_CharT, _Traits>& out,
						  const _CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<_CharT, _Traits>       ostream_type;
	typedef typename ostream_type::ios_base    ios_base;

	const std::streamsize put = out.rdbuf()->sputn(s, n);
	if (put != n)
		out.setstate(ios_base::badbit);
}

template<typename _CharT, typename _Traits>
inline void ostream_fill(std::basic_ostream<_CharT, _Traits>& out,
						 std::streamsize n)
{
	typedef std::basic_ostream<_CharT, _Traits>       ostream_type;
	typedef typename ostream_type::ios_base    ios_base;

	const _CharT c = out.fill();
	for (; n > 0; --n)
	{
		const typename _Traits::int_type put = out.rdbuf()->sputc(c);
		if (_Traits::eq_int_type(put, _Traits::eof()))
		{
			out.setstate(ios_base::badbit);
			break;
		}
	}
}

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_insert(std::basic_ostream<_CharT, _Traits>& out,
			   const _CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<_CharT, _Traits>       ostream_type;
	typedef typename ostream_type::ios_base    ios_base;

	typename ostream_type::sentry cerb(out);
	if (cerb)
	{
		const std::streamsize w = out.width();
		if (w > n)
		{
			const bool left = ((out.flags()
			& ios_base::adjustfield)
			== ios_base::left);
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

}

#endif