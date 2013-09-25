#ifndef _FALCON_FUNCTIONAL_CALL_PARTIAL_RECURSIVE_PARAM_HPP
#define _FALCON_FUNCTIONAL_CALL_PARTIAL_RECURSIVE_PARAM_HPP

#include <falcon/functional/call.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>
#include <falcon/math/min.hpp>

namespace falcon {

template<std::size_t NumberArg, std::size_t N>
struct __call_partial_recursive_param_loop
{
  static_assert(NumberArg > 1, "NumberArg < 2");

  template<typename Function, typename... Args,
    std::size_t Start = (N - 1) * (NumberArg - 1) + NumberArg + 1>
  static constexpr auto impl(Function func, Args&&... args)
  -> decltype(call(
    typename parameter_index_cat<
      parameter_index<0>,
      build_range_parameter_index_t<
        Start,
        min(Start + (NumberArg - 1), sizeof...(Args) + 1)
      >
    >::type(),
    func,
    __call_partial_recursive_param_loop<NumberArg, N-1>
    ::impl(func, std::forward<Args>(args)...),
    std::forward<Args>(args)...
  ))
  {
    return call(
      typename parameter_index_cat<
        parameter_index<0>,
        build_range_parameter_index_t<
          Start,
          min(Start + (NumberArg - 1), sizeof...(Args) + 1)
        >
      >::type(),
      func,
      __call_partial_recursive_param_loop<NumberArg, N-1>
      ::impl(func, std::forward<Args>(args)...),
      std::forward<Args>(args)...
    );
  }
};

template<std::size_t NumberArg>
struct __call_partial_recursive_param_loop<NumberArg, 0>
{
  static_assert(NumberArg > 1, "NumberArg < 2");

  template<typename Function, typename... Args>
  static constexpr auto impl(Function func, Args&&... args)
  -> decltype(call(
    build_parameter_index_t<min(NumberArg, sizeof...(Args))>(),
    func,
    std::forward<Args>(args)...
  ))
  {
    return call(
      build_parameter_index_t<min(NumberArg, sizeof...(Args))>(),
      func,
      std::forward<Args>(args)...
    );
  }
};


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
template<std::size_t NumberArg, typename Function, typename... Args,
  std::size_t N = (sizeof...(Args) - 2) / (NumberArg - 1)>
constexpr auto call_partial_recursive_param_loop(Function func, Args&&... args)
-> decltype(__call_partial_recursive_param_loop<NumberArg, N>
            ::impl(func, std::forward<Args>(args)...))
{
  return __call_partial_recursive_param_loop<NumberArg, N>
  ::impl(func, std::forward<Args>(args)...);
}

}

#endif
