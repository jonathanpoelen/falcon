#ifndef FALCON_FUNCTIONAL_CALL_HPP
#define FALCON_FUNCTIONAL_CALL_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/arg/arg.hpp>

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
template <typename Function, typename... Args, std::size_t... Indexes>
constexpr auto call(const parameter_index<Indexes...>&, Function && func, Args&&... args)
-> decltype(std::forward<Function>(func)(arg<Indexes>(std::forward<Args>(args)...)...))
{    return std::forward<Function>(func)(arg<Indexes>(std::forward<Args>(args)...)...); }
//@}

}

#endif
