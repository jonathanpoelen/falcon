#ifndef FALCON_CAST_STATIC_CASTER_HPP
#define FALCON_CAST_STATIC_CASTER_HPP

#include <utility>

namespace falcon {

/// Wrapper for static_cast
template <class Cast>
struct static_caster
{
  constexpr static_caster() noexcept {}

  template<class T>
  Cast operator()(T&& d) const
  { return static_cast<Cast>(std::forward<T>(d)); }
};

}

#endif
