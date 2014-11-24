#ifndef FALCON_FN_FRONT_HPP
#define FALCON_FN_FRONT_HPP

#include <falcon/type_traits/static_const.hpp>

#include <cstddef>

namespace falcon {
namespace fn {

/// \brief call T::front()
/// If an array is passed, the first element is returned.
struct front_fn
{
  constexpr front_fn() noexcept {}

  template<class T>
  constexpr auto operator()(T && x) const
  noexcept(noexcept(x.front()))
  -> decltype(x.front())
  { return x.front() ; }

  template<class T, std::size_t N>
  constexpr T const &
  front(T const (&arr)[N]) noexcept
  { return arr[0]; }

  template<class T, std::size_t N>
  T & front(T (&arr)[N]) noexcept
  { return arr[0]; }
};

FALCON_GLOBAL_OBJECT(front, front_fn);

}
}

#endif
