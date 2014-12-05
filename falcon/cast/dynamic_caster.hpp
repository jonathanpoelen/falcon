#ifndef FALCON_CAST_DYNAMIC_CASTER_HPP
#define FALCON_CAST_DYNAMIC_CASTER_HPP

#include <utility>

namespace falcon {

/// Wrapper for dynamic_cast
template <typename Cast>
struct dynamic_caster
{
  constexpr dynamic_caster() noexcept {}

  template<class T>
  Cast operator()(T&& d) const
  { return dynamic_cast<Cast>(std::forward<T>(d)); }
};

}

#endif
