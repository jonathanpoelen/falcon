#ifndef FALCON_FUNCTIONAL_CALL_PARTIAL_RECURSIVE_PARAM_HPP
#define FALCON_FUNCTIONAL_CALL_PARTIAL_RECURSIVE_PARAM_HPP

#include <falcon/math/min.hpp>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/invoke.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

namespace falcon {

namespace _aux {
  template<std::size_t NumberArg, std::size_t N>
  struct call_partial_recursive_param_loop
  {
    static_assert(NumberArg > 1, "NumberArg < 2");

    template<typename Function, typename... Args
    , std::size_t Start = (N - 1) * (NumberArg - 1) + NumberArg + 1>
    static constexpr CPP1X_DELEGATE_FUNCTION(
      impl(Function func, Args&&... args)
    , invoke(
        typename parameter_index_cat<
          parameter_index<0>,
          build_range_parameter_index_t<
            Start
          , min(Start + (NumberArg - 1), sizeof...(Args) + 1)
          >
        >::type()
      , func
      , call_partial_recursive_param_loop<NumberArg, N-1>
        ::impl(func, std::forward<Args>(args)...)
      , std::forward<Args>(args)...
      )
    )
  };

  template<std::size_t NumberArg>
  struct call_partial_recursive_param_loop<NumberArg, 0>
  {
    static_assert(NumberArg > 1, "NumberArg < 2");

    template<typename Function, typename... Args>
    static constexpr CPP1X_DELEGATE_FUNCTION(
      impl(Function func, Args&&... args)
    , invoke(
        build_parameter_index_t<min(NumberArg, sizeof...(Args))>()
      , func
      , std::forward<Args>(args)...
      )
    )
  };
}


/**
 * \brief Call \c func with \c _NumberArg arguments. The return of \c func is the first argument of next call.
 * \return Last operations.
 *
 * \code
 * int n = call_partial_param_loop<2>(accu_t(), 1,2,3,4,5,6);
 * \endcode
 * equivalent to
 * \code
 * accu_t accu;
 * int n = accu(accu(accu(accu(accu(1,2),3),4),5),6);
 * \endcode
 *
 * \ingroup call-arguments
 */
template<std::size_t NumberArg, typename Function, typename... Args
, std::size_t N = (sizeof...(Args) - 2) / (NumberArg - 1)>
constexpr CPP1X_DELEGATE_FUNCTION(
  call_partial_recursive_param_loop(Function func, Args&&... args)
, _aux::call_partial_recursive_param_loop<NumberArg, N>
  ::impl(func, std::forward<Args>(args)...)
)

}

#endif
