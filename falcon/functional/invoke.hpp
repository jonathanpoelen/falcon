#ifndef FALCON_FUNCTIONAL_INVOKE_HPP
#define FALCON_FUNCTIONAL_INVOKE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/arg.hpp>
#include <falcon/type_traits/static_const.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <functional>

namespace falcon {

struct invoke_fn
{
  constexpr invoke_fn() noexcept {}

  /**
   * Invoke a function object, which may be either a member pointer or a
   * function object. The first parameter will tell which.
   * @{
   */
  template<class F, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(F && f, Args&&... args) const
  , std::forward<F>(f)(std::forward<Args>(args)...))

  template<class T, class C, class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T C::* fp, C* p, Args&&... args) const
  , std::mem_fn(fp)(p, std::forward<Args>(args)...))
  /**
   * @}
   */

  /**
   * \brief Call \c f with the indexes \c Idx for arguments \c args
   *
   * \code
   * invoke(parameter_index<0,2,0,1>(), f, 1,2,3,4,5);
   * \endcode
   * equivalent to
   * \code
   * f(1,3,1,2);
   * \endcode
   * @{
   */
  template<class F, class... Args, std::size_t... Idx>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(parameter_index<Idx...>, F && f, Args&&... args) const
  , std::forward<F>(f)(arg<Idx>(std::forward<Args>(args)...)...))

  template<class T, class C, class... Args, std::size_t... Idx>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(parameter_index<Idx...>, T C::* fp, C* p, Args&&... args) const
  , std::mem_fn(fp)(p, arg<Idx>(std::forward<Args>(args)...)...))
  /**
   * @}
   */
};

namespace {
  constexpr auto const & invoke = static_const<invoke_fn>::value;
}

}

#endif
