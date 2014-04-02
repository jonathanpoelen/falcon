#ifndef FALCON_CAST_STATIC_CASTER_HPP
#define FALCON_CAST_STATIC_CASTER_HPP

#if __cplusplus >= 201103L
# include <utility>
#else
# include <falcon/c++/noexcept.hpp>
#endif

namespace falcon {

/// Wrapper for static_cast
template <class Cast>
struct static_caster
{
#if __cplusplus >= 201103L
  template<class T>
  Cast operator()(T&& d) const noexcept
  { return static_cast<Cast>(std::forward<T>(d)); }
#else
  template<class T>
  Cast operator()(T& d) const CPP_NOEXCEPT
  { return static_cast<Cast>(d); }

  template<class T>
  Cast operator()(const T& d) const CPP_NOEXCEPT
  { return static_cast<Cast>(d); }
#endif
};

}

#endif
