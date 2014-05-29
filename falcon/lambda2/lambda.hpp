#ifndef FALCON_LAMBDA2_LAMBDA_HPP
#define FALCON_LAMBDA2_LAMBDA_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/preprocessor/d_punctuation.hpp>

#include <tuple>
#include <iosfwd>
#include <utility>
#include <functional>

namespace falcon {
namespace lambda2 {

namespace _aux {

template<class Op, class T = void, class U = void>
struct lambda;

template<class F>
struct func_t;

template<
  class T
, class Remove = typename std::remove_reference<T>::type
, bool = std::is_bind_expression<T>::value>
struct to_lambda_impl
{ using type = lambda<Remove>; };

template<class T, class Remove>
struct to_lambda_impl<T, Remove, true>
{ using type = lambda<func_t<Remove>>; };

template<class T, class Remove, std::size_t N>
struct to_lambda_impl<T, Remove[N], false>
{ using type = lambda<Remove(&)[N]>; };

template<class T>
using to_lambda = typename to_lambda_impl<T>::type;


template<class L>
struct lambda_operators
{
  typedef lambda_operators operators_type;

  template<class I>
  constexpr lambda<arrow<>, L, I>
  operator[](I pos) const noexcept
  { return {arrow<>(), static_cast<const L&>(*this), std::move(pos)}; }

  template<class T2>
  constexpr lambda<affect<>, L, to_lambda<T2>>
  operator=(T2 && x) const noexcept
  { return {affect<>(), static_cast<const L&>(*this)
  , to_lambda<T2>{std::forward<T2>(x)}}; }

  template<class T2, class Class>
  constexpr auto
#ifdef IN_IDE_PARSER
  operator->
#else
  operator->*
#endif
  (T2 Class::* mem) const noexcept
  -> lambda<decltype(std::mem_fn(mem)), L>
  { return {std::mem_fn(mem), static_cast<const L&>(*this)}; }
};

template<class... Elements>
struct lambda_with_tuple
{
  typedef lambda_with_tuple with_tuple_type;

  std::tuple<Elements...> t;

  template<class... Args>
  constexpr lambda_with_tuple(Args&&... args)
  : t(std::forward<Args>(args)...)
  {}

  template<class T>
  constexpr lambda_with_tuple(T&& x)
  : t(std::move(x.t))
  {}

  template<class T>
  constexpr lambda_with_tuple(T const & x)
  : t(x.t)
  {}
};

template<class Op, class T, class U>
struct lambda
: lambda_operators<lambda<Op, T, U>>
, lambda_with_tuple<Op, T, U>
{
  using lambda::with_tuple_type::lambda_with_tuple;
  using lambda::operators_type::operator=;

  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
  , std::get<0>(this->t)(
      std::get<1>(this->t)(std::forward<Args>(args)...)
    , std::get<2>(this->t)(std::forward<Args>(args)...)
    )
  )
};

template<class Op, class T>
struct lambda<Op, T, void>
: lambda_operators<lambda<Op, T>>
, lambda_with_tuple<Op, T>
{
  using lambda::with_tuple_type::lambda_with_tuple;
  using lambda::operators_type::operator=;

  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
  , std::get<0>(this->t)(
      std::get<1>(this->t)(std::forward<Args>(args)...)
    )
  )
};

template<class T>
struct lambda<T, void, void>
: lambda_operators<lambda<T>>
{
  T x;

  using lambda::operators_type::operator=;

  template<class U>
  constexpr lambda(U && xx)
  : x(std::forward<U>(xx))
  {}

  template<class... Args>
  constexpr T operator()(Args&&...) const
  { return x; }
};

template<int N>
struct lambda<std::integral_constant<int, N>, void, void>
: lambda_operators<lambda<std::integral_constant<int, N>>>
{
  using lambda::operators_type::operator=;

  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(Args&&... args) const
  , std::get<N-1>(std::forward_as_tuple(std::forward<Args>(args)...))
  )
};


struct bind_t {};

template<class F>
struct lambda<func_t<F>, void, void>
: lambda_operators<lambda<func_t<F>>>
{
  F f;

  template<class... Args>
  constexpr lambda(Args&&... args)
  : f(std::forward<Args>(args)...)
  {}

  template<class... Args>
  constexpr lambda(bind_t, Args&&... args)
  : f(std::bind(std::forward<Args>(args)...))
  {}

  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Args&&... args) const
  , f(std::forward<Args>(args)...)
  )
};


template<class T, bool = std::is_bind_expression<T>::value>
struct to_lambda_ref_impl
{ using type = lambda<T&>; };

template<class T>
struct to_lambda_ref_impl<T, true>
{ using type = lambda<func_t<T>>; };

template<class T, std::size_t N>
struct to_lambda_ref_impl<T[N], false>
{ using type = lambda<func_t<T>>; };

template<class T>
using to_lambda_ref = typename to_lambda_ref_impl<T>::type;


#define FALCON_MAKE_OPERATOR(op, func_op)                                   \
  template<class Op1, class T1, class U1, class Op2, class T2, class U2>    \
  constexpr lambda<func_op<>, lambda<Op1, T1, U1>, lambda<Op2, T2, U2>>     \
  operator op (lambda<Op1, T1, U1> l, lambda<Op2, T2, U2> r) noexcept       \
  { return {func_op<>(), std::move(l), std::move(r)}; }                     \
                                                                            \
  template<class Op1, class T1, class U1, class T>                          \
  constexpr lambda<func_op<>, lambda<Op1, T1, U1>, to_lambda<T>>            \
  operator op (lambda<Op1, T1, U1> l, T && r) noexcept                      \
  { return {func_op<>(), std::move(l), to_lambda<T>{std::forward<T>(r)}}; } \
                                                                            \
  template<class T, class Op1, class T1, class U1>                          \
  constexpr lambda<func_op<>, to_lambda<T>, lambda<Op1, T1, U1>>            \
  operator op (T && l, lambda<Op1, T1, U1> r) noexcept                      \
  { return {func_op<>(), to_lambda<T>{std::forward<T>(l)}, std::move(r)}; }

FALCON_MAKE_OPERATOR(+,  plus)
FALCON_MAKE_OPERATOR(-,  minus)
FALCON_MAKE_OPERATOR(*,  multiplies)
FALCON_MAKE_OPERATOR(/,  divides)
FALCON_MAKE_OPERATOR(%,  modulus)
FALCON_MAKE_OPERATOR(<<, left_shift)
FALCON_MAKE_OPERATOR(>>, right_shift)
FALCON_MAKE_OPERATOR(&,  bit_and)
FALCON_MAKE_OPERATOR(|,  bit_or)
FALCON_MAKE_OPERATOR(^,  bit_xor)

FALCON_MAKE_OPERATOR(==, equal_to)
FALCON_MAKE_OPERATOR(!=, not_equal_to)
FALCON_MAKE_OPERATOR(>,  greater)
FALCON_MAKE_OPERATOR(<,  less)
FALCON_MAKE_OPERATOR(>=, greater_equal)
FALCON_MAKE_OPERATOR(<=, less_equal)
FALCON_MAKE_OPERATOR(&&, logical_and)
FALCON_MAKE_OPERATOR(||, logical_or)

FALCON_MAKE_OPERATOR(FALCON_PP_D_COMMA, comma)

#define FALCON_MAKE_OPERATOR_EQUAL(op, func_op)                      \
  FALCON_MAKE_OPERATOR(op, func_op)                                  \
                                                                     \
  template<class T, class Op1, class T1, class U1>                   \
  constexpr lambda<func_op<>, to_lambda_ref<T>, lambda<Op1, T1, U1>> \
  operator op (T & l, lambda<Op1, T1, U1> r) noexcept                \
  { return {func_op<>(), to_lambda_ref<T>{l}, std::move(r)}; }

FALCON_MAKE_OPERATOR_EQUAL(+=,  plus_equal)
FALCON_MAKE_OPERATOR_EQUAL(-=,  minus_equal)
FALCON_MAKE_OPERATOR_EQUAL(*=,  multiplies_equal)
FALCON_MAKE_OPERATOR_EQUAL(/=,  divides_equal)
FALCON_MAKE_OPERATOR_EQUAL(%=,  modulus_equal)
FALCON_MAKE_OPERATOR_EQUAL(<<=, left_shift_equal)
FALCON_MAKE_OPERATOR_EQUAL(>>=, right_shift_equal)
FALCON_MAKE_OPERATOR_EQUAL(&=,  bit_and_equal)
FALCON_MAKE_OPERATOR_EQUAL(|=,  bit_or_equal)
FALCON_MAKE_OPERATOR_EQUAL(^=,  bit_xor_equal)

#undef FALCON_MAKE_OPERATOR_EQUAL
#undef FALCON_MAKE_OPERATOR

#define FALCON_MAKE_OPERATOR(op, func_op)       \
  template<class Op, class T, class U>          \
  constexpr lambda<func_op<>, lambda<Op, T, U>> \
  operator op (lambda<Op, T, U> x) noexcept     \
  { return {func_op<>(), std::move(x)}; }

FALCON_MAKE_OPERATOR(-, unary_negate)
FALCON_MAKE_OPERATOR(+, unary_plus)
FALCON_MAKE_OPERATOR(!, binary_negate)
FALCON_MAKE_OPERATOR(~, bit_not)
FALCON_MAKE_OPERATOR(&, address)
FALCON_MAKE_OPERATOR(*, pointer)
FALCON_MAKE_OPERATOR(++, increment)
FALCON_MAKE_OPERATOR(--, decrement)

#undef FALCON_MAKE_OPERATOR

template<class Op, class T, class U>
constexpr lambda<post_increment<>, lambda<Op, T, U>>
operator++(lambda<Op, T, U> x, int) noexcept
{ return {post_increment<>(), std::move(x) }; }

template<class Op, class T, class U>
constexpr lambda<post_decrement<>, lambda<Op, T, U>>
operator--(lambda<Op, T, U> x, int) noexcept
{ return {post_decrement<>(), std::move(x) }; }


template<class CharT, class Traits, class Op1, class T1, class U1>
constexpr lambda<left_shift<>
, lambda<std::basic_ostream<CharT, Traits>&>
, lambda<Op1, T1, U1>>
operator << ( std::basic_ostream<CharT, Traits> & l
            , lambda<Op1, T1, U1> r) noexcept
{ return {left_shift<>()
, lambda<std::basic_ostream<CharT, Traits>&>{l}
, std::move(r)
}; }

template<class CharT, class Traits, class Op1, class T1, class U1>
constexpr lambda<right_shift<>
, lambda<std::basic_istream<CharT, Traits>&>
, lambda<Op1, T1, U1>>
operator >> ( std::basic_istream<CharT, Traits> & l
            , lambda<Op1, T1, U1> r) noexcept
{ return {right_shift<>()
, lambda<std::basic_istream<CharT, Traits>&>{l}
, std::move(r)
}; }

}


template<int N>
using placeholder = _aux::lambda<std::integral_constant<int, N>>;

namespace placeholders {
  constexpr placeholder<1> _1;
  constexpr placeholder<2> _2;
  constexpr placeholder<3> _3;
  constexpr placeholder<4> _4;
  constexpr placeholder<5> _5;
  constexpr placeholder<6> _6;
  constexpr placeholder<7> _7;
  constexpr placeholder<8> _8;
  constexpr placeholder<9> _9;
}

template<class T>
constexpr _aux::lambda<T&>
var(T& x)
{ return {x}; }

template<class T>
constexpr _aux::lambda<typename std::remove_reference<T>::type>
constant(T && x)
{ return {std::forward<T>(x)}; }

template<class F>
constexpr _aux::lambda<_aux::func_t<F>>
func(F && f)
{ return {std::forward<F>(f)}; }

template<class F, class... Args>
constexpr _aux::lambda<_aux::func_t<
  decltype(std::bind(std::declval<F>(), std::declval<Args>()...))
>>
bind(F && f, Args&&... args)
{ return {_aux::bind_t(), std::forward<F>(f), std::forward<Args>(args)...}; }

}
}

namespace std {
  template<int I>
  struct is_placeholder<
    ::falcon::lambda2::_aux::lambda<integral_constant<int, I>>
  > : integral_constant<int, I>
  {};
}

#endif
