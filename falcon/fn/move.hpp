#ifndef FALCON_FN_MOVE_HPP
#define FALCON_FN_MOVE_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call std::forward< T>(x)
struct forward_fn {
  constexpr forward_fn() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(
    operator()(T && x) const
  , std::forward<T>(x))
};

/// \brief call std::move(x)
struct move_fn {
  constexpr move_fn() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(
    operator()(T && x) const
  , std::move(std::forward<T>(x)))
};

/// \brief call std::move_if_noexcept(x)
struct move_if_noexcept_fn {
  constexpr move_if_noexcept_fn() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(
    operator()(T && x) const
  , std::move_if_noexcept(std::forward<T>(x)))
};

FALCON_GLOBAL_OBJECT(forward, forward_fn);
FALCON_GLOBAL_OBJECT(move, move_fn);
FALCON_GLOBAL_OBJECT(move_if_noexcept, move_if_noexcept_fn);

}
}

#endif
