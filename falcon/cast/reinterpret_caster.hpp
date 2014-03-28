#ifndef FALCON_CAST_REINTERPRET_CASTER_HPP
#define FALCON_CAST_REINTERPRET_CASTER_HPP

#include <falcon/c++/noexcept.hpp>

namespace falcon {

/// Wrapper for reinterpret_cast
template <typename Cast>
struct reinterpret_caster
{
  template<typename T>
  Cast operator()(T& d) const CPP_NOEXCEPT
  { return reinterpret_cast<Cast>(d); }

  template<typename T>
  Cast operator()(const T& d) const CPP_NOEXCEPT
  { return reinterpret_cast<Cast>(d); }
};

}

#endif
