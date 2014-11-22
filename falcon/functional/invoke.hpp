#ifndef FALCON_FUNCTIONAL_INVOKE_HPP
#define FALCON_FUNCTIONAL_INVOKE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <functional>

namespace falcon {

/**
 * Invoke a function object, which may be either a member pointer or a
 * function object. The first parameter will tell which.
 */
struct invoke_fn
{
  constexpr invoke_fn() noexcept {}

  template<class T, class C, class... Args>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T C::* fp, C* p, Args&&... args) const
  , std::mem_fn(fp)(p, std::forward<Args>(args)...))

  template<class F, class... Args>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(F && f, Args&&... args) const
  , std::forward<F>(f)(std::forward<Args>(args)...))
};

/**
 * Invoke a function object, which may be either a member pointer or a
 * function object. The first parameter will tell which.
 */
constexpr auto const & invoke = static_const<invoke_fn>::value;

}

#endif
