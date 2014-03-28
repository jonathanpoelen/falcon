#ifndef FALCON_CAST_CONST_CASTER_HPP
#define FALCON_CAST_CONST_CASTER_HPP

#include <falcon/c++/noexcept.hpp>

namespace falcon {

/// Wrapper for const_cast
template <typename Cast>
struct const_caster
{
  template<typename T>
  Cast operator()(T& d) const CPP_NOEXCEPT
  { return const_cast<Cast>(d); }

  template<typename T>
  Cast operator()(const T& d) const CPP_NOEXCEPT
  { return const_cast<Cast>(d); }
};

}

#endif
