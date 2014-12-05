#ifndef FALCON_CAST_CONST_CASTER_HPP
#define FALCON_CAST_CONST_CASTER_HPP

#include <utility>

namespace falcon {

/// Wrapper for const_cast
template <typename Cast>
struct const_caster
{
  constexpr const_caster() noexcept {}

  template<class T>
  Cast operator()(T&& d) const
  { return const_cast<Cast>(std::forward<T>(d)); }
};

}

#endif
