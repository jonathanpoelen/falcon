#ifndef FALCON_CAST_DYNAMIC_CASTER_HPP
#define FALCON_CAST_DYNAMIC_CASTER_HPP

#include <falcon/c++/noexcept.hpp>

namespace falcon {

/// Wrapper for dynamic_cast
template <typename Cast>
struct dynamic_caster
{
  template<typename T>
  Cast operator()(T& d) const CPP_NOEXCEPT
  { return dynamic_cast<Cast>(d); }

  template<typename T>
  Cast operator()(const T& d) const CPP_NOEXCEPT
  { return dynamic_cast<Cast>(d); }
};

}

#endif
