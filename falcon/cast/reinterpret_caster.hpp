#ifndef FALCON_CAST_REINTERPRET_CASTER_HPP
#define FALCON_CAST_REINTERPRET_CASTER_HPP

#include <utility>

namespace falcon {

/// Wrapper for reinterpret_cast
template <typename Cast>
struct reinterpret_caster
{
  constexpr reinterpret_caster() noexcept {}

  template<class T>
  Cast operator()(T&& d) const
  { return reinterpret_cast<Cast>(std::forward<T>(d)); }
};

}

#endif
