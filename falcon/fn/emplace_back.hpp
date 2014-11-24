#ifndef FALCON_FN_EMPLACE_BACK_HPP
#define FALCON_FN_EMPLACE_BACK_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::emplace_back()
struct emplace_back_fn
{
  constexpr emplace_back_fn() noexcept {}

  template<class T, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, Args && ... args) const
  , std::forward<T>(x).emplace_back(std::forward<Args>(args)...))
};

FALCON_GLOBAL_OBJECT(emplace_back, emplace_back_fn);

}
}

#endif
