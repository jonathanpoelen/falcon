#ifndef FALCON_FN_PUSH_HPP
#define FALCON_FN_PUSH_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/fn/make_global_function_object.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::push(U)
struct push_fn {
  constexpr push_fn() noexcept {}

  template<class T, class U>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, U && y) const
  , x.push(std::forward<U>(y)))
};

FALCON_GLOBAL_OBJECT(push, push_fn);

}
}

#endif
