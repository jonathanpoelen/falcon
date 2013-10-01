#ifndef _FALCON_FLAG_ISTREAM_HPP
#define _FALCON_FLAG_ISTREAM_HPP

#include <ios>
#include <falcon/flag/flag.hpp>

namespace falcon {
namespace istream {
namespace flag {

template<typename _CharT, typename _Traits, typename _T>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, falcon::flag<_T>& /*flag*/)
{
// 	typedef typename _Traits::char_type char_type;
// 	typedef std::basic_istream<_CharT, _Traits> istream_type;
// 	typedef typename istream_type::ios_base ios_base;
// 	typedef falcon::flag<choose, _BaseInt> flag_type;
//
// 	flag = 0;
// 	typename istream_type::sentry sentry(is);
// 	if (sentry)
// 	{
// 		const char_type zero = is.widen('0');
// 		const char_type one = is.widen('1');
// 		typename ios_base::iostate state = ios_base::goodbit;
// 		typedef typename flag_type::int_type int_type;
// 		unsigned int n = choose;
// 		for (int_type mask = int_type(1) << (choose - 1); n; --n, mask >>= 1)
// 		{
// 			static typename _Traits::int_type eof = _Traits::eof();
//
// 			typename _Traits::int_type c1 = is.rdbuf()->sbumpc();
// 			if (_Traits::eq_int_type(c1, eof))
// 			{
// 				state |= ios_base::eofbit;
// 				break;
// 			}
// 			else
// 			{
// 				const char_type c2 = _Traits::to_char_type(c1);
// 				if (_Traits::eq(c2, zero))
// 					;
// 				else if (_Traits::eq(c2, one))
// 					flag |= mask;
// 				else
// 				{
// 					if (_Traits::eq_int_type(is.rdbuf()->sputbackc(c2), eof))
// 						state |= ios_base::failbit;
// 					break;
// 				}
// 			}
// 		}
// 		if (n)
// 			flag >>= n;
// 		flag.clean();
// 		if (state)
// 			is.setstate(state);
// 	}

	return is;
}

template<typename _CharT, typename _Traits, typename _BaseInt>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, falcon::flag<void>&)
{ return is; }

}
}
}

using namespace falcon::istream::flag;

#endif
