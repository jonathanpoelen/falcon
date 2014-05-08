#ifndef FALCON_IOSTREAM_IMANIP_HPP
#define FALCON_IOSTREAM_IMANIP_HPP

#include <istream>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace iostreams {

typedef std::istream&(*imanip_type)(std::istream&);
typedef std::wistream&(*wimanip_type)(std::wistream&);

namespace _aux {
  struct ws_t
  {
    template<class CharT, class Traits>
    std::basic_istream<CharT, Traits>&
    operator()(std::basic_istream<CharT, Traits>& is) const
    { return is >> std::ws; }

    operator imanip_type () const
    { return std::ws; }

    operator wimanip_type () const
    { return std::ws; }
  };
}

template<class CharT, class Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, _aux::ws_t)
{ return is >> std::ws; }

/// Manipulator functor for std::ws
CPP_CONSTEXPR_OR_CONST _aux::ws_t ws;

}
}

#endif
