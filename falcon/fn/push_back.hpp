#ifndef FALCON_FN_PUSH_BACK_HPP
#define FALCON_FN_PUSH_BACK_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/fn/make_global_function_object.hpp>

#include <utility>

namespace falcon {
namespace fn {

/// \brief call T::push_back(U)
struct push_back_fn {
  constexpr push_back_fn() noexcept {}

  template<class T, class U>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x, U && y) const
  , x.push_back(std::forward<U>(y)))
};

FALCON_GLOBAL_OBJECT(push_back, push_back_fn);

}
}

#endif
