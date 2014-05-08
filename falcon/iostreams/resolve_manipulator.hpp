#ifndef FALCON_IOSTREAM_RESOLVE_MANIPULATOR_HPP
#define FALCON_IOSTREAM_RESOLVE_MANIPULATOR_HPP

#include <iosfwd>

namespace falcon {
namespace iostreams {

namespace _aux {
  template<class CharT, class Traits>
  struct resolve_manipulator
  {
    typedef std::basic_ostream<CharT, Traits>&(
      *type
    )(std::basic_ostream<CharT, Traits>&);
  };
}

#if __cplusplus >= 201103L
template<class CharT = char, class Traits = std::char_traits<CharT> >
#else
template<class CharT, class Traits>
#endif
inline typename _aux::resolve_manipulator<CharT, Traits>::type
resolve_manipulator(typename _aux::resolve_manipulator<CharT, Traits>::type f)
{ return f; }

template<class CharT, class Traits>
inline typename _aux::resolve_manipulator<CharT, Traits>::type
resolve_manipulator(const std::basic_ostream<CharT, Traits>&,
										typename _aux::resolve_manipulator<CharT, Traits>::type f)
{ return f; }

inline std::ostream&(*ostream_manipulator(std::ostream&(*f)(std::ostream&)))(std::ostream&)
{ return f; }

inline std::wostream&(*wostream_manipulator(std::wostream&(*f)(std::wostream&)))(std::wostream&)
{ return f; }

}
}

#endif
