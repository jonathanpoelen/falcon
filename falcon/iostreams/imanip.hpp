#ifndef FALCON_IOSTREAM_IMANIP_HPP
#define FALCON_IOSTREAM_IMANIP_HPP

#include <istream>
#include <falcon/type_traits/static_const.hpp>

namespace falcon {
namespace iostreams {

typedef std::istream&(*imanip_type)(std::istream&);
typedef std::wistream&(*wimanip_type)(std::wistream&);

namespace aux_ {
  struct ws_t
  {
    constexpr ws_t() noexcept {}

    template<class CharT, class Traits>
    std::basic_istream<CharT, Traits>&
    operator()(std::basic_istream<CharT, Traits>& is) const
    { return is >> std::ws; }

    operator imanip_type () const noexcept
    { return std::ws; }

    operator wimanip_type () const noexcept
    { return std::ws; }
  };

  template<class CharT, class Traits>
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, aux_::ws_t)
  { return is >> std::ws; }
}

/// Manipulator functor for std::ws
FALCON_GLOBAL_OBJECT(ws, aux_::ws_t);

}
}

#endif
