#ifndef FALCON_FN_EMPLACE_FRONT_HPP
#define FALCON_FN_EMPLACE_FRONT_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::emplace_front()
struct emplace_front_fn
{
  constexpr emplace_front_fn() noexcept {}

  template<class T, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, Args && ... args) const
  , std::forward<T>(x).emplace_front(std::forward<Args>(args)...))
};

FALCON_GLOBAL_OBJECT(emplace_front, emplace_front_fn);

}
}

#endif
