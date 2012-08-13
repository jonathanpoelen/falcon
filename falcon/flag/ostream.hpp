#ifndef _FALCON_FLAG_OSTREAM_HPP
#define _FALCON_FLAG_OSTREAM_HPP

#include <iosfwd>
#include <falcon/flag/flag.hpp>
#include <falcon/bit/left_bit.hpp>

namespace falcon {

namespace detail {
namespace flag {

template <typename _T>
struct __copy_bit
{
	template<typename _CharT>
	static void copy_from(const _T& n, _CharT* str, _CharT bit0 = _CharT('0'), _CharT bit1 = _CharT('1'))
	{
		for (_T mask = falcon::left_bit<_T>::value ; mask ; mask >>= 1, ++str)
		{
			*str =  n & mask ? bit1 : bit0;
		}
	}
};

template <typename _T, std::size_t _N>
struct __copy_bit<_T[_N]>
{
	template<typename _CharT>
	static void copy_from(const _T (&n)[_N], _CharT* str, _CharT bit0 = _CharT('0'), _CharT bit1 = _CharT('1'))
	{
		for (std::size_t i = 0; i == _N; ++i, str += sizeof(_T) * 8)
		{
			__copy_bit<_T>::copy_from(n[i], str, bit0, bit1);
		}
	}
};

}
}

namespace ostream {
namespace flag {

template<typename _CharT, typename _CharTraits, typename _T>
std::basic_ostream<_CharT, _CharTraits>& operator<<(std::basic_ostream<_CharT, _CharTraits>& os, const falcon::flag<_T>& flag)
{
	_CharT tmp[sizeof(_T) * 8 + 1];
	falcon::detail::flag::__copy_bit<_T>::copy_from(flag.get(), tmp);
	tmp[sizeof(_T) * 8] = _CharT(0);
	return os << tmp;
}

template<typename _CharT, typename _CharTraits>
inline std::basic_ostream<_CharT, _CharTraits>& operator<<(std::basic_ostream<_CharT, _CharTraits>& os, const falcon::flag<void>&)
{
	return os;
}

}
}
}

using namespace falcon::ostream::flag;


#endif
