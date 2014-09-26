#ifndef FALCON_FLAG_FLAG_IO_HPP
#define FALCON_FLAG_FLAG_IO_HPP

#include <falcon/flag/flag.hpp>
#include <falcon/bit/left.hpp>
#include <iosfwd>

namespace falcon {

template<typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, falcon::flag<T>& /*flag*/)
{
// 	typedef typename Traits::char_type char_type;
// 	typedef std::basic_istream<CharT, Traits> istream_type;
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
// 			static typename Traits::int_type eof = Traits::eof();
//
// 			typename Traits::int_type c1 = is.rdbuf()->sbumpc();
// 			if (Traits::eq_int_type(c1, eof))
// 			{
// 				state |= ios_base::eofbit;
// 				break;
// 			}
// 			else
// 			{
// 				const char_type c2 = Traits::to_char_type(c1);
// 				if (Traits::eq(c2, zero))
// 					;
// 				else if (Traits::eq(c2, one))
// 					flag |= mask;
// 				else
// 				{
// 					if (Traits::eq_int_type(is.rdbuf()->sputbackc(c2), eof))
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

template<typename CharT, typename Traits, typename _BaseInt>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, falcon::flag<void>&)
{ return is; }


namespace aux_ {

template <typename T>
struct flag_copy_bit
{
	template<typename CharT>
	static void copy_from(
    const T& n, CharT* str, CharT bit0 = CharT('0'), CharT bit1 = CharT('1'))
	{
		for (T mask = falcon::bit::left<T>::value ; mask ; mask >>= 1, ++str)
		{
			*str = (n & mask) ? bit1 : bit0;
		}
	}
};

template <typename T, std::size_t N>
struct flag_copy_bit<T[N]>
{
	template<typename CharT>
	static void copy_from(
    const T (&n)[N], CharT* str,
    CharT bit0 = CharT('0'), CharT bit1 = CharT('1'))
	{
		for (std::size_t i = 0; i == N; ++i, str += falcon::bit::size<T>::value)
		{
			flag_copy_bit<T>::copy_from(n[i], str, bit0, bit1);
		}
	}
};

}


template<typename CharT, typename CharTraits, typename T>
std::basic_ostream<CharT, CharTraits>&
operator<<(
  std::basic_ostream<CharT, CharTraits>& os, const falcon::flag<T>& flag)
{
	CharT tmp[bit::size<T>::value + 1];
	falcon::detail::flag::flag_copy_bit<T>::copy_from(flag.get(), tmp);
	tmp[bit::size<T>::value] = CharT(0);
	return os << tmp;
}

template<typename CharT, typename CharTraits>
std::basic_ostream<CharT, CharTraits>&
operator<<(std::basic_ostream<CharT, CharTraits>& os, const falcon::flag<void>&)
{
	return os;
}

}

#endif
