#ifndef FALCON_FUNCTIONAL_INVOKE_HPP
#define FALCON_FUNCTIONAL_INVOKE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <functional>

namespace falcon {

/**
 * Invoke a function object, which may be either a member pointer or a
 * function object. The first parameter will tell which.
 */
constexpr struct invoke_t {
template<class T, class C, class... Args>
  CPP1X_DELEGATE_FUNCTION(
    operator()(T C::* fp, C* p, Args&&... args) const
  , std::mem_fn(fp)(p, std::forward<Args>(args)...))

  template<class F, class... Args>
  CPP1X_DELEGATE_FUNCTION(
    operator()(F && f, Args&&... args) const
  , std::forward<F>(f)(std::forward<Args>(args)...))
} invoke;

}

#endif
