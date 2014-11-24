#ifndef FALCON_FN_EMPLACE_HPP
#define FALCON_FN_EMPLACE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::emplace()
struct emplace_fn
{
  constexpr emplace_fn() noexcept {}

  template<class T, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, Args && ... args) const
  , std::forward<T>(x).emplace(std::forward<Args>(args)...))
};

FALCON_GLOBAL_OBJECT(emplace, emplace_fn);

}
}

#endif
