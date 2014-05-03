#ifndef FALCON_FUNCTIONAL_CALL_PARTIAL_PARAM_LOOP_HPP
#define FALCON_FUNCTIONAL_CALL_PARTIAL_PARAM_LOOP_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

namespace _aux {
  template<std::size_t NumberArg, typename F,
    typename... Args, std::size_t... Indexes>
  void call_partial_param_loop(parameter_index<Indexes...>,
                               F && func, Args&&... args)
  {
    FALCON_UNPACK(call(
      build_range_parameter_index_t<
        Indexes * NumberArg
      , Indexes * NumberArg + NumberArg
      >()
    , std::forward<F>(func)
    , std::forward<Args>(args)...
    ));
  }
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
template<std::size_t NumberArg, typename F, typename... Args
, std::size_t N = sizeof...(Args) / NumberArg - ((sizeof...(Args) % NumberArg) ? 0 : 1)
, typename Indexes = build_parameter_index_t<N>
, typename LastIndexes = build_range_parameter_index_t<N*NumberArg, sizeof...(Args)>
>
auto call_partial_param_loop(F func, Args&&... args)
-> decltype(call(LastIndexes(), std::forward<F>(func), std::forward<Args>(args)...))
{
  _aux::call_partial_param_loop<NumberArg>(Indexes(), func, std::forward<Args>(args)...);
  return call(LastIndexes(), std::forward<F>(func), std::forward<Args>(args)...);
}

}

#endif
