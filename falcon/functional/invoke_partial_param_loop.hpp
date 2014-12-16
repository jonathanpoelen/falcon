#ifndef FALCON_FUNCTIONAL_INVOKE_PARTIAL_PARAM_LOOP_HPP
#define FALCON_FUNCTIONAL_INVOKE_PARTIAL_PARAM_LOOP_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/utility/unpack.hpp>
#include <falcon/functional/invoke.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template<std::size_t NumberArg>
class invoke_partial_param_loop_fn
{
  template<class F, class... Args, std::size_t... Indexes>
  static void impl_(
    parameter_index<Indexes...>, F && func, Args&&... args)
  {
    FALCON_UNPACK(invoke(
      build_range_parameter_index_t<
        Indexes * NumberArg
      , Indexes * NumberArg + NumberArg
      >()
    , std::forward<F>(func)
    , std::forward<Args>(args)...
    ));
  }

public:
  constexpr invoke_partial_param_loop_fn() noexcept {}

  template<
    class F, class... Args
  , std::size_t N = sizeof...(Args) / NumberArg
      - ((sizeof...(Args) % NumberArg) ? 0 : 1)
  , class Indexes = build_parameter_index_t<N>
  , class LastIndexes = build_range_parameter_index_t<
      N*NumberArg, sizeof...(Args)
    >
  >
  auto operator()(F && func, Args&&... args) const
  -> decltype(invoke(
    LastIndexes(), std::forward<F>(func), std::forward<Args>(args)...))
  {
    impl_(Indexes(), func, std::forward<Args>(args)...);
    return invoke(
      LastIndexes(), std::forward<F>(func), std::forward<Args>(args)...);
  }
};

/**
 * \brief Call \c func with \c NumberArg arguments at the same time.
 * \return Last operations.
 *
 * \code
 * int n = invoke_partial_param_loop<2>(accu_t(), 1,2,3,4,5,6);
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
template<std::size_t NumberArg, class F, class... Args>
CPP1X_DELEGATE_FUNCTION(
  invoke_partial_param_loop(F func, Args&&... args)
, invoke_partial_param_loop_fn<NumberArg>()(
    std::forward<F>(func), std::forward<Args>(args)...
  )
)

}

#endif
