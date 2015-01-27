#ifndef FALCON_FUNCTIONAL_TO_COMPILE_TIME_EXPRESSION_HPP
#define FALCON_FUNCTIONAL_TO_COMPILE_TIME_EXPRESSION_HPP

#include <falcon/parameter/parameter_pack.hpp>

#include <utility>

namespace falcon {

template<class Result, class... Elements, class F>
constexpr Result
to_compile_time_expression_impl(parameter_pack<Elements...>, F && f)
{ return std::forward<F>(f)(Elements()...); }

template<class Result = void, class... Elements, class F, class... Ts>
constexpr Result to_compile_time_expression_impl(
  parameter_pack<Elements...>, F && f, bool val, Ts... values
) {
  return val
  ? to_compile_time_expression_impl<Result>(
    parameter_pack<Elements..., std::true_type>()
  , std::forward<F>(f), values...)
  : to_compile_time_expression_impl<Result>(
    parameter_pack<Elements..., std::false_type>()
  , std::forward<F>(f), values...);
}

template<class Result = void, class F, class... Ts>
constexpr Result to_compile_time_expression(F && f, Ts... values)
{
  return to_compile_time_expression_impl<Result>(
    parameter_pack<>(), std::forward<F>(f), values...
  );
}

}

#endif
