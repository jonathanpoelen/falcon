#ifndef FALCON_FUNCTIONAL_MIN_MAX_HPP
#define FALCON_FUNCTIONAL_MIN_MAX_HPP

#include <falcon/functional/operators.hpp>

#include <tuple>
#include <algorithm>

namespace falcon {

template <class Cmp = less<>>
struct basic_min
{
  constexpr basic_min() {}

  constexpr basic_min(Cmp const & cmp)
  : cmp_(cmp)
  {}

  constexpr basic_min(Cmp && cmp)
  : cmp_(std::move(cmp))
  {}

private:
  Cmp cmp_;

public:
  template<class T, class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T const & a, T const & b, Ts const &... args) const
  , std::min({a, b, args...}, this->cmp_))

  template<class T, class U>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T const & a, U const & b) const
  , std::min(a, b, this->cmp_))
};

/// \example min(fn::lt)(a, b, c)
template<class F = less<>>
basic_min<F> min(F f = F())
{ return {std::move(f)}; }


template <class Cmp = less<>>
struct basic_max
{
  constexpr basic_max() {}

  constexpr basic_max(Cmp const & cmp)
  : cmp_(cmp)
  {}

  constexpr basic_max(Cmp && cmp)
  : cmp_(std::move(cmp))
  {}

private:
  Cmp cmp_;

public:
  template<class T, class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T const & a, T const & b, Ts const &... args) const
  , std::max({a, b, args...}, this->cmp_))

  template<class T, class U>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T const & a, U const & b) const
  , std::max(a, b, this->cmp_))
};

/// \example max(fn::lt)(a, b, c)
template<class F = less<>>
basic_max<F> max(F f = F())
{ return {std::move(f)}; }

}

#endif
