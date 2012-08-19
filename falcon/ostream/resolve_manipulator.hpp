#ifndef _FALCON_OSTREAM_RESOLVE_MANIPULATOR_HPP
#define _FALCON_OSTREAM_RESOLVE_MANIPULATOR_HPP

#include <iosfwd>

namespace falcon {
namespace ostream {

template<typename _CharT, typename _Traits>
struct __resolve_manipulator
{
	typedef std::basic_ostream<_CharT, _Traits>&(*__type)(std::basic_ostream<_CharT, _Traits>&);
};

template<typename _CharT = char, typename _Traits = std::char_traits<_CharT> >
inline typename __resolve_manipulator<_CharT, _Traits>::__type resolve_manipulator(typename __resolve_manipulator<_CharT, _Traits>::__type f)
{
	return f;
}

template<typename _CharT, typename _Traits>
inline typename __resolve_manipulator<_CharT, _Traits>::__type resolve_manipulator(const std::basic_ostream<_CharT, _Traits>&, typename __resolve_manipulator<_CharT, _Traits>::__type f)
{
	return f;
}

inline std::ostream&(*ostream_manipulator(std::ostream&(*f)(std::ostream&)))(std::ostream&)
{
	return f;
}

inline std::wostream&(*wostream_manipulator(std::wostream&(*f)(std::wostream&)))(std::wostream&)
{
	return f;
}

}
}

#endif
