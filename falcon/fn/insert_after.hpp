#ifndef FALCON_FN_INSERT_AFTER_HPP
#define FALCON_FN_INSERT_AFTER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::insert_after(args...)
struct insert_after_fn
{
  constexpr insert_after_fn() noexcept {}

  template<class T, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, Args && args) const
  , std::forward<T>(x).insert_after(std::forward<Args>(args)...))
};

FALCON_GLOBAL_OBJECT(insert_after, insert_after_fn);

}
}

#endif
