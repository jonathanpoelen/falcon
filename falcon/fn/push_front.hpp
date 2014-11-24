#ifndef FALCON_FN_PUSH_FRONT_HPP
#define FALCON_FN_PUSH_FRONT_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/fn/make_global_function_object.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::push_front(U)
struct push_front_fn {
  constexpr push_front_fn() noexcept {}

  template<class T, class U>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, U && y) const
  , x.push_front(std::forward<U>(y)))
};

FALCON_GLOBAL_OBJECT(push_front, push_front_fn);

}
}

#endif
