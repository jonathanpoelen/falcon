#ifndef FALCON_FN_EMPTY_HPP
#define FALCON_FN_EMPTY_HPP

#include <falcon/type_traits/static_const.hpp>

#include <cstddef>

namespace falcon {
namespace fn {

/// \brief call T::empty()
/// If an array is passed, the last element is returned.
struct empty_fn
{
  constexpr empty_fn() noexcept {}

  template<class T>
  constexpr bool operator()(T && x) const
  noexcept(noexcept(x.empty()))
  { return x.empty() ; }

  template<class T, std::size_t N>
  constexpr bool
  empty(T const (&)[N]) noexcept
  { return false; }
};

FALCON_GLOBAL_OBJECT(empty, empty_fn);

}
}

#endif
