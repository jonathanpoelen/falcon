#ifndef FALCON_FUNCTIONAL_IF_ELSE_HPP
#define FALCON_FUNCTIONAL_IF_ELSE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/cast/static_caster.hpp>

#include <tuple>
#include <utility>
#include <type_traits>

namespace falcon {

template <class T, class U = T, class Test = static_caster<bool> >
struct basic_if_else
{
  struct is_transparent;

  constexpr basic_if_else() {}

  template<class T2, class U2>
  constexpr basic_if_else(T2 && x, U2 && y)
  : t_(std::forward<T2>(x), std::forward<U2>(y), Test())
  {}

  template<class T2, class U2, class Test2>
  constexpr basic_if_else(T2 && x, U2 && y, Test2 && test)
  : t_(std::forward<T2>(x), std::forward<U2>(y), std::forward<Test2>(test))
  {}

private:
  std::tuple<T, U, Test> t_;

  T const & a_() const noexcept { return std::get<0>(this->t_); }
  U const & b_() const noexcept { return std::get<1>(this->t_); }

  template<class... Args>
  constexpr bool test_(Args&&... args) const
  noexcept(noexcept(std::get<2>(this->t_)(std::forward<Args>(args)...)))
  { return std::get<2>(this->t_)(std::forward<Args>(args)...); }

public:
  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Args... args) const
  , test_(std::forward<Args>(args)...) ? this->a_() : this->b_())
};

/**
 * if_else(a, b, test)(args) equivalent to test(args)?a:b
 */
template<class T, class U, class Test = static_caster<bool>>
basic_if_else<
  typename std::decay<T>::type
, typename std::decay<U>::type
, typename std::decay<Test>::type>
if_else(T && x, U && y, Test && test = Test())
{ return {
  std::forward<T>(x), std::forward<U>(y), std::forward<Test>(test)
}; }


template <class T, class U = T, class Test = static_caster<bool> >
struct basic_if_else2
{
  struct is_transparent;

  constexpr basic_if_else2() {}

  template<class T2, class U2>
  constexpr basic_if_else2(T2 && x, U2 && y)
  : t_(std::forward<T2>(x), std::forward<U2>(y), Test())
  {}

  template<class T2, class U2, class Test2>
  constexpr basic_if_else2(T2 && x, U2 && y, Test2 && test)
  : t_(std::forward<T2>(x), std::forward<U2>(y), std::forward<Test2>(test))
  {}

private:
  std::tuple<T, U, Test> t_;

  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    a_(Args && ... args) const
  , std::get<0>(this->t_)(std::forward<Args>(args)...))

  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    b_(Args && ... args) const
  , std::get<1>(this->t_)(std::forward<Args>(args)...))

  template<class... Args>
  constexpr bool test_(Args const & ... args) const
  noexcept(noexcept(std::get<2>(this->t_)(args...)))
  { return std::get<2>(this->t_)(args...); }

public:
  template<class... Args>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Args... args) const
  , test_(args...)
    ? this->a_(std::forward<Args>(args)...)
    : this->b_(std::forward<Args>(args)...))
};

/**
 * if_else2(a, b, test)(args) equivalent to test(args)?a(args):b(args)
 */
template<class F1, class F2, class Test = static_caster<bool>>
basic_if_else2<
  typename std::decay<F1>::type
, typename std::decay<F2>::type
, typename std::decay<Test>::type>
if_else2(F1 && f1, F2 && f2, Test && test = Test())
{ return {
  std::forward<F1>(f1), std::forward<F2>(f2), std::forward<Test>(test)
}; }

}

#endif
