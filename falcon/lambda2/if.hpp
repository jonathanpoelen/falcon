#ifndef FALCON_LAMBDA2_IF_HPP
#define FALCON_LAMBDA2_IF_HPP

#include <falcon/lambda2/lambda.hpp>

namespace falcon {
namespace lambda2 {

namespace _aux {

  template<class>
  class condition_t;

  template<class Condition, class ThenPart>
  struct lambda<condition_t<Condition>, ThenPart, void>
  : lambda_with_tuple<Condition, ThenPart>
  {
    using lambda_with_tuple<Condition, ThenPart>::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      if (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class ThenPart, class ElsePart>
  struct lambda<condition_t<Condition>, ThenPart, ElsePart>
  : lambda_with_tuple<Condition, ThenPart, ElsePart>
  {
    using lambda_with_tuple<Condition, ThenPart, ElsePart>::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      if (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        std::get<1>(this->t)(std::forward<Args>(args)...);
      }
      else  {
        std::get<2>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class>
  class condition_return_t;

  template<class Condition, class ThenPart, class ElsePart>
  struct lambda<condition_return_t<Condition>, ThenPart, ElsePart>
  : lambda_with_tuple<Condition, ThenPart, ElsePart>
  {
    using lambda_with_tuple<Condition, ThenPart, ElsePart>::lambda_with_tuple;

    template<class... Args>
    constexpr CPP1X_DELEGATE_FUNCTION(
      operator()(Args&&... args) const
    , std::get<0>(this->t)(std::forward<Args>(args)...)
      ? std::get<1>(this->t)(std::forward<Args>(args)...)
      : std::get<2>(this->t)(std::forward<Args>(args)...)
    )
  };

  template<class>
  class if_else_t;

  template<class Condition>
  struct lambda<condition_t<Condition>, void, void>
  {
    Condition cond;

    template<class... Args>
    void operator()(Args&&...) const
    { static_assert(true, "contains no body"); }

    template<class ThenPart>
    constexpr lambda<if_else_t<Condition>
    , typename std::remove_reference<ThenPart>::type>
    operator[](ThenPart && then_part)
    { return {cond, std::forward<ThenPart>(then_part)}; }
  };

  template<class Condition, class ThenPart>
  struct lambda<if_else_t<Condition>, ThenPart, void>
  : lambda<condition_t<Condition>, ThenPart>
  {
    using lambda<condition_t<Condition>, ThenPart>::lambda;

    template<class C>
    struct else_t
    {
      lambda & l;

      template<class ElsePart>
      constexpr lambda<C, ThenPart
      , typename std::remove_reference<ElsePart>::type>
      operator[](ElsePart && else_part)
      { return {std::get<0>(l.t)
      , std::get<1>(l.t)
      , std::forward<ElsePart>(else_part)}; }
    };

    else_t<condition_t<Condition>> else_ = {*this};
    else_t<condition_return_t<Condition>> else_return = {*this};
  };

}

template<class Condition>
constexpr
_aux::lambda<_aux::condition_t<typename std::remove_reference<Condition>::type>>
if_(Condition && cond)
{ return {std::forward<Condition>(cond)}; }

template<class Condition, class ThenPart>
constexpr _aux::lambda<
  _aux::condition_t<typename std::remove_reference<Condition>::type>
, typename std::remove_reference<ThenPart>::type>
if_(Condition && cond, ThenPart && then_part)
{ return {std::forward<Condition>(cond)
, std::forward<ThenPart>(then_part)}; }

template<class Condition, class ThenPart, class ElsePart>
constexpr _aux::lambda<
  _aux::condition_t<typename std::remove_reference<Condition>::type>
, typename std::remove_reference<ThenPart>::type
, typename std::remove_reference<ElsePart>::type>
if_(Condition && cond, ThenPart && then_part, ElsePart && else_part)
{ return {std::forward<Condition>(cond)
, std::forward<ThenPart>(then_part)
, std::forward<ElsePart>(else_part)}; }

template<class Condition, class ThenPart, class ElsePart>
constexpr _aux::lambda<
  _aux::condition_t<typename std::remove_reference<Condition>::type>
, typename std::remove_reference<ThenPart>::type
, typename std::remove_reference<ElsePart>::type>
if_else(Condition && cond, ThenPart && then_part, ElsePart && else_part)
{ return {std::forward<Condition>(cond)
, std::forward<ThenPart>(then_part)
, std::forward<ElsePart>(else_part)}; }

template<class Condition, class ThenPart, class ElsePart>
constexpr _aux::lambda<
  _aux::condition_return_t<typename std::remove_reference<Condition>::type>
, typename std::remove_reference<ThenPart>::type
, typename std::remove_reference<ElsePart>::type>
if_else_return(Condition && cond, ThenPart && then_part, ElsePart && else_part)
{ return {std::forward<Condition>(cond)
, std::forward<ThenPart>(then_part)
, std::forward<ElsePart>(else_part)}; }

}
}

#endif
