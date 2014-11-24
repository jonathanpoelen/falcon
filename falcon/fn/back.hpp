#ifndef FALCON_FN_BACK_HPP
#define FALCON_FN_BACK_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <cstddef>

namespace falcon {
namespace fn {

/// \brief call T::back()
/// If an array is passed, the last element is returned.
struct back_fn
{
  constexpr back_fn() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x) const
  , x.back())

  template<class T, std::size_t N>
  constexpr T const &
  back(T const (&arr)[N]) noexcept
  { return arr[0]; }

  template<class T, std::size_t N>
  T & back(T (&arr)[N]) noexcept
  { return arr[0]; }
};

FALCON_GLOBAL_OBJECT(back, back_fn);

}
}

#endif
