#ifndef _FALCON_OSTREAM_INSERT_HPP
#define _FALCON_OSTREAM_INSERT_HPP

#include <iosfwd>
#include <falcon/string/cstringfwd.hpp>

namespace falcon {

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_write(std::basic_ostream<_CharT, _Traits>& out,
							const _CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<_CharT, _Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	if (out.rdbuf()->sputn(s, n) != n)
		out.setstate(ios_base::badbit);

	return out;
}

template<typename _CharT, typename _Traits, std::size_t _N>
std::basic_ostream<_CharT, _Traits>&
ostream_write(std::basic_ostream<_CharT, _Traits>& out,
							const _CharT (&s)[_N])
{ return ostream_write<>(out, s, static_cast<std::streamsize>(_N)); }

template<typename _CharT, typename _Traits, typename _Alloc>
std::basic_ostream<_CharT, _Traits>&
ostream_write(std::basic_ostream<_CharT, _Traits>& out,
							const std::basic_string<_CharT, _Traits, _Alloc>& s)
{ return ostream_write<>(out, s.data(), s.size()); }

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_write(std::basic_ostream<_CharT, _Traits>& out,
							const basic_cstring<_CharT, _Traits>& s)
{ return ostream_write<>(out, s.data(), s.size()); }

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_write(std::basic_ostream<_CharT, _Traits>& out,
							const basic_cstring<const _CharT, _Traits>& s)
{ return ostream_write<>(out, s.data(), s.size()); }

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_fill(std::basic_ostream<_CharT, _Traits>& out, std::streamsize n, _CharT c)
{
	typedef std::basic_ostream<_CharT, _Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	for (; n > 0; --n)
	{
		if (_Traits::eq_int_type(out.rdbuf()->sputc(c), _Traits::eof()))
		{
			out.setstate(ios_base::badbit);
			break;
		}
	}

	return out;
}

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_fill(std::basic_ostream<_CharT, _Traits>& out, std::streamsize n)
{ return ostream_fill(out, n, out.fill()); }

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_insert(std::basic_ostream<_CharT, _Traits>& out,
							 const _CharT* s, std::streamsize n)
{
	typedef std::basic_ostream<_CharT, _Traits> ostream_type;
	typedef typename ostream_type::ios_base ios_base;

	typename ostream_type::sentry cerb(out);
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

template<typename _CharT, typename _Traits, std::size_t _N>
std::basic_ostream<_CharT, _Traits>&
ostream_insert(std::basic_ostream<_CharT, _Traits>& out,
							 const _CharT(&s)[_N])
{ return ostream_insert<>(out, s, static_cast<std::streamsize>(_N)); }

template<typename _CharT, typename _Traits, typename _Alloc>
std::basic_ostream<_CharT, _Traits>&
ostream_insert(std::basic_ostream<_CharT, _Traits>& out,
							 const std::basic_string<_CharT, _Traits, _Alloc>& s)
{ return ostream_insert<>(out, s.data(), s.size()); }

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_insert(std::basic_ostream<_CharT, _Traits>& out,
							 const basic_cstring<_CharT, _Traits>& s)
{ return ostream_insert<>(out, s.data(), s.size()); }

template<typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
ostream_insert(std::basic_ostream<_CharT, _Traits>& out,
							 const basic_cstring<const _CharT, _Traits>& s)
{ return ostream_insert<>(out, s.data(), s.size()); }

}

#endif