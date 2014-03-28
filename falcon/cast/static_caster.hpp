#ifndef FALCON_CAST_STATIC_CASTER_HPP
#define FALCON_CAST_STATIC_CASTER_HPP

#include <falcon/c++/noexcept.hpp>

namespace falcon {

/// Wrapper for static_cast
template <class Cast>
struct static_caster
{
  template<class T>
  Cast operator()(T& d) const CPP_NOEXCEPT
  { return static_cast<Cast>(d); }

  template<class T>
  Cast operator()(const T& d) const CPP_NOEXCEPT
  { return static_cast<Cast>(d); }
};

}

#endif
