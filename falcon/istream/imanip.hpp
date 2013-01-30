#ifndef FALCON_ISTREAM_IMANIP_HPP
#define FALCON_ISTREAM_IMANIP_HPP

#include <istream>
#include <falcon/c++/constexpr.hpp>

namespace std {
	template<typename _CharT, typename _Traits>
	basic_istream<_CharT, _Traits>&
	ws(basic_istream<_CharT, _Traits>& __is);
}

namespace falcon {
namespace istream {

typedef std::istream&(*imanip_type)(std::istream&);
typedef std::wistream&(*wimanip_type)(std::wistream&);

struct __ws
{
	template<typename _CharT, typename _Traits>
	std::basic_istream<_CharT, _Traits>&
	operator()(std::basic_istream<_CharT, _Traits>& __is) const
	{ return __is >> std::ws; }

	operator imanip_type () const
	{ return std::ws; }

	operator wimanip_type () const
	{ return std::ws; }
};

template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>&
operator>>(std::basic_istream<_CharT, _Traits>& __is, __ws)
{ return __is >> std::ws; }

/// Manipulator functor for std::ws
CPP_USE_CONSTEXPR __ws ws;

}
}

#endif