#ifndef _FALCON_FUNCTIONAL_CALL_PARTIAL_PARAM_LOOP_HPP
#define _FALCON_FUNCTIONAL_CALL_PARTIAL_PARAM_LOOP_HPP

#include <falcon/c++1x/unpack.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template<std::size_t NumberArg, typename Function,
  typename... Args, std::size_t... Indexes>
void __call_partial_param_loop(parameter_index<Indexes...>,
                               Function func, Args&&... args)
{
  CPP1X_UNPACK(call(
    build_range_parameter_index_t<
      Indexes * NumberArg,
      Indexes * NumberArg + NumberArg
    >(),
    func,
    std::forward<Args>(args)...
  ));
}

/**
 * \brief Call \c func with \c _NumberArg arguments at the same time.
 * \return Last operations.
 *
 * \code
 * int n = call_partial_param_loop<2>(accu_t(), 1,2,3,4,5,6);
 * \endcode
 * equivalent to
 * \code
 * accu_t accu;
 * accu(1,2);
 * accu(3,4);
 * int n = accu(5,6);
 * \endcode
 *
 * \ingroup call-arguments
 */
template<std::size_t NumberArg, typename Function, typename... Args,
  std::size_t N = sizeof...(Args) / NumberArg - ((sizeof...(Args) % NumberArg) ? 0 : 1),
  typename Indexes = build_parameter_index_t<N>,
  typename LastIndexes = build_range_parameter_index_t<N*NumberArg, sizeof...(Args)>
>
auto call_partial_param_loop(Function func, Args&&... args)
-> decltype(call(LastIndexes(), func, std::forward<Args>(args)...))
{
  __call_partial_param_loop<NumberArg>(Indexes(), func, std::forward<Args>(args)...);
  return call(LastIndexes(), func, std::forward<Args>(args)...);
}

}

#endif
