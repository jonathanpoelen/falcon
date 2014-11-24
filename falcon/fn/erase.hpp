#ifndef FALCON_FN_ERASE_HPP
#define FALCON_FN_ERASE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::erase(args...)
struct erase_fn
{
  constexpr erase_fn() noexcept {}

  template<class T, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, Args && args) const
  , std::forward<T>(x).erase(std::forward<Args>(args)...))
};

FALCON_GLOBAL_OBJECT(erase, erase_fn);

}
}

#endif
