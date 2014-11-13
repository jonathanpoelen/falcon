#ifndef FALCON_FN_OPERATORS_UTILITY_HPP
#define FALCON_FN_OPERATORS_UTILITY_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/cast/static_caster.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/fn/operators/operators.hpp>

#include <tuple>
#include <algorithm>

namespace falcon {
namespace fn {
namespace op {

namespace aux_ {
  template <class Comp, bool val>
  struct check_if_impl
  {
    typedef ::falcon::aux_::is_transparent_t is_transparent;

    constexpr check_if_impl() {}

    constexpr check_if_impl(Comp const & cmp)
    : cmp_(cmp)
    {}

    constexpr check_if_impl(Comp && cmp)
    : cmp_(static_cast<Comp&&>(cmp))
    {}

    template<class T, class U>
    constexpr bool operator()(T const& a, U const& b) const noexcept
    { return cmp_(a, b); }

    template<class T, class U, class... Ts>
    constexpr bool
    operator()(T const& a, U const& b, Ts const&... args) const noexcept
    { return bool(cmp_(a, b)) == val ? val : operator()(b, args...); }

  private:
    Comp cmp_;
  };
}

template<class Cmp>
using each_fn = aux_::check_if_impl<Cmp, false>;

template<class Cmp>
using any_fn = aux_::check_if_impl<Cmp, true>;

template<class Cmp>
each_fn<Cmp> each(Cmp cmp)
{ return {std::move(cmp)}; }

template<class Cmp>
any_fn<Cmp> any(Cmp cmp)
{ return {std::move(cmp)}; }


template <class F>
struct reduce_fn
: is_transparent_inheritance<F>
{
  constexpr reduce_fn() {}

  constexpr reduce_fn(F const & fn)
  : fn_(fn)
  {}

  constexpr reduce_fn(F && fn)
  : fn_(static_cast<F&&>(fn))
  {}

private:
  F fn_;

public:
  template<class T, class U>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && a, U && b) const
  , this->fn_(std::forward<T>(a), std::forward<U>(b)))

  template<class T, class U, class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && a, U && b, Ts &&... args) const
  , operator()(
    this->fn_(std::forward<T>(a), std::forward<U>(b)), std::forward<Ts>(args)...
  ))
};

template<class F>
reduce_fn<F> reduce(F f)
{ return {std::move(f)}; }


template <class F>
struct apply_fn
{
  constexpr apply_fn() {}

  constexpr apply_fn(F const & fn)
  : fn_(fn)
  {}

  constexpr apply_fn(F && fn)
  : fn_(static_cast<F&&>(fn))
  {}

  template<class... Ts>
  void operator()(Ts &&... args) const
  noexcept(noexcept(FALCON_UNPACK(
    std::declval<F const&>()(std::forward<Ts>(args)))))
  { FALCON_UNPACK(fn_(std::forward<Ts>(args))); }

private:
  F fn_;
};

template<class F>
apply_fn<F> apply(F f)
{ return {std::move(f)}; }


template <class Cmp = lt_fn>
struct min_fn
{
  typedef ::falcon::aux_::is_transparent_t is_transparent;

  constexpr min_fn() {}

  constexpr min_fn(Cmp const & cmp)
  : cmp_(cmp)
  {}

  constexpr min_fn(Cmp && cmp)
  : cmp_(static_cast<Cmp&&>(cmp))
  {}

private:
  Cmp cmp_;

public:
  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts const &... args) const
  , std::min({args...}, this->cmp_))
};

template<class F = lt_fn>
min_fn<F> min(F f = lt_fn())
{ return {std::move(f)}; }


template <class Cmp = lt_fn>
struct max_fn
{
  typedef ::falcon::aux_::is_transparent_t is_transparent;

  constexpr max_fn() {}

  constexpr max_fn(Cmp const & cmp)
  : cmp_(cmp)
  {}

  constexpr max_fn(Cmp && cmp)
  : cmp_(static_cast<Cmp&&>(cmp))
  {}

private:
  Cmp cmp_;

public:
  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts const &... args) const
  , std::max({args...}, this->cmp_))
};

template<class F = lt_fn>
max_fn<F> max(F f = lt_fn())
{ return {std::move(f)}; }


template <class T, class U = T, class Test = static_caster<bool> >
struct if_else_fn
{
  typedef ::falcon::aux_::is_transparent_t is_transparent;

  constexpr if_else_fn() {}

  template<class T2, class U2>
  constexpr if_else_fn(T2 && x, U2 && y)
  : t_(std::forward<T2>(x), std::forward<U2>(y), Test())
  {}

  template<class T2, class U2, class Test2>
  constexpr if_else_fn(T2 && x, U2 && y, Test2 && test)
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

template<class T, class U>
if_else_fn<
  typename std::decay<T>::type
, typename std::decay<U>::type>
if_else(T && x, U && y)
{ return {std::forward<T>(x), std::forward<U>(y)}; }

template<class T, class U, class Test>
if_else_fn<
  typename std::decay<T>::type
, typename std::decay<U>::type
, Test>
if_else(T && x, U && y, Test test)
{ return {std::forward<T>(x), std::forward<U>(y), std::move(test)}; }

}
}

namespace ops = fn::op;

}

#endif
