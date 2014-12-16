#ifndef FALCON_FUNCTIONAL_INVOKE_PARTIAL_RECURSIVE_PARAM_HPP
#define FALCON_FUNCTIONAL_INVOKE_PARTIAL_RECURSIVE_PARAM_HPP

#include <falcon/math/min.hpp>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/invoke.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

#include <utility>

namespace falcon {

template<std::size_t NumberArg>
class invoke_partial_recursive_param_loop_fn
{
  static_assert(NumberArg > 1, "NumberArg < 2");

  template<std::size_t N, class = void>
  struct Impl {
    template<
      class F, class... Args
    , std::size_t Start = (N - 1) * (NumberArg - 1) + NumberArg + 1>
    static constexpr CPP1X_DELEGATE_FUNCTION(
      impl_(F && func, Args&&... args)
    , invoke(
        typename parameter_index_cat<
          parameter_index<0>,
          build_range_parameter_index_t<
            Start
          , min(Start + (NumberArg - 1), sizeof...(Args) + 1)
          >
        >::type()
      , std::forward<F>(func)
      , Impl<N-1>::impl_(std::forward<F>(func), std::forward<Args>(args)...)
      , std::forward<Args>(args)...
      )
    )
  };

  template<class T>
  struct Impl<0, T> {
    template<class F, class... Args>
    static constexpr CPP1X_DELEGATE_FUNCTION(
      impl_(F && func, Args&&... args)
    , invoke(
        build_parameter_index_t<min(NumberArg, sizeof...(Args))>()
      , std::forward<F>(func)
      , std::forward<Args>(args)...
      )
    )
  };

public:
  constexpr invoke_partial_recursive_param_loop_fn() noexcept {}

  template<
    class F, class... Args
  , std::size_t N = (sizeof...(Args) - 2) / (NumberArg - 1)>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(F && func, Args&&... args) const
  , Impl<N>::impl_(std::forward<F>(func), std::forward<Args>(args)...)
  )
};


/**
 * \brief Call \c func with \c NumberArg arguments. The return of \c func is the first argument of next call.
 * \return Last operations.
 *
 * \code
 * int n = invoke_partial_param_loop<2>(accu_t(), 1,2,3,4,5,6);
 * \endcode
 * equivalent to
 * \code
 * accu_t accu;
 * int n = accu(accu(accu(accu(accu(1,2),3),4),5),6);
 * \endcode
 *
 * \ingroup call-arguments
 */
template<std::size_t NumberArg, class F, class... Args>
constexpr CPP1X_DELEGATE_FUNCTION(
  invoke_partial_recursive_param_loop(F func, Args&&... args)
, invoke_partial_recursive_param_loop_fn<NumberArg>()(
    std::forward<F>(func), std::forward<Args>(args)...)
)

}

#endif
