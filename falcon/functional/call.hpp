#ifndef FALCON_FUNCTIONAL_CALL_HPP
#define FALCON_FUNCTIONAL_CALL_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/arg.hpp>

#include <utility>

namespace falcon {

/**
 * \addtogroup call-arguments
 * @{
 */
/**
 * \brief Call \c func with the indexes \c Indexes for arguments \c args
 *
 * \code
 * call(parameter_index<0,2,0,1>(), f, 1,2,3,4,5);
 * \endcode
 * equivalent to
 * \code
 * f(1,3,1,2);
 * \endcode
 */
constexpr struct call_t
{
  constexpr call_t() {}

  template <typename Function, typename... Args, std::size_t... Indexes>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(const parameter_index<Indexes...>&, Function && func, Args&&... args) const
  , std::forward<Function>(func)(arg<Indexes>(std::forward<Args>(args)...)...))
} call;
//@}

}

#endif
