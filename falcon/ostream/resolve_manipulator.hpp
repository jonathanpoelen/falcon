#ifndef FALCON_OSTREAM_RESOLVE_MANIPULATOR_HPP
#define FALCON_OSTREAM_RESOLVE_MANIPULATOR_HPP

#include <iosfwd>

namespace falcon {
namespace ostream {

template<typename CharT, typename Traits>
struct __resolve_manipulator
{
	typedef std::basic_ostream<CharT, Traits>&(
		*__type
	)(std::basic_ostream<CharT, Traits>&);
};

#if __cplusplus >= 201103L
template<typename CharT = char, typename Traits = std::char_traits<CharT> >
#else
template<typename CharT, typename Traits>
#endif
inline typename __resolve_manipulator<CharT, Traits>::__type
resolve_manipulator(typename __resolve_manipulator<CharT, Traits>::__type f)
{
	return f;
}

template<typename CharT, typename Traits>
inline typename __resolve_manipulator<CharT, Traits>::__type
resolve_manipulator(const std::basic_ostream<CharT, Traits>&,
										typename __resolve_manipulator<CharT, Traits>::__type f)
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
