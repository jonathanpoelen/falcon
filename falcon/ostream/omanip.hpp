#ifndef FALCON_OSTREAM_OMANIP_HPP
#define FALCON_OSTREAM_OMANIP_HPP

#include <ostream>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace ostream {

typedef std::ostream&(*omanip_type)(std::ostream&);
typedef std::wostream&(*womanip_type)(std::wostream&);

#define __FALCON_CREATE_OMANIP(manipulator)\
struct __##manipulator\
{\
	template<typename _CharT, typename _Traits>\
	std::basic_ostream<_CharT, _Traits>&\
	operator()(std::basic_ostream<_CharT, _Traits>& __os) const\
	{ return __os << std::manipulator; }\
	\
	operator omanip_type () const\
	{ return std::manipulator; }\
	\
	operator womanip_type () const\
	{ return std::manipulator; }\
};\
\
template<typename _CharT, typename _Traits>\
std::basic_ostream<_CharT, _Traits>&\
operator<<(std::basic_ostream<_CharT, _Traits>& __os, __##manipulator)\
{ return __os << std::manipulator; }\
\
/**\
 * Manipulator functor for std::manipulator\
 */\
CPP_CONSTEXPR_OR_CONST __##manipulator manipulator;

/**
 * Manipulators functors for std::endl, std::ends and std::flush
 * @{
 */
__FALCON_CREATE_OMANIP(endl)
__FALCON_CREATE_OMANIP(ends)
__FALCON_CREATE_OMANIP(flush)
// @}

#undef __FALCON_CREATE_OMANIP

}
}

#endif
