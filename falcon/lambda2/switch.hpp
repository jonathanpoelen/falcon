#ifndef FALCON_LAMBDA2_SWITCH_HPP
#define FALCON_LAMBDA2_SWITCH_HPP

#include <falcon/lambda2/lambda.hpp>

namespace falcon {
namespace lambda2 {

namespace _aux {

  struct switch_action_default
  {
    template<class... Args>
    constexpr void operator()(Args const &...) const noexcept {
    }
  };

  template<long long Label, class Func>
  struct case_action
  {
    typedef Func type;
    static const long long label = Label;

    Func act;

    template<class... Args>
    constexpr void operator()(Args && ... args) const {
      act(std::forward<Args...>(args...));
    }
  };

  template<class Func>
  struct case_default
  {
    Func act;

    template<class... Args>
    constexpr void operator()(Args && ... args) const {
      act(std::forward<Args...>(args...));
    }
  };

  template<class Default = switch_action_default, class... Cases>
  class switch_action;

  template<class Condition, class Default>
  struct lambda<Condition, switch_action<Default>>
  : lambda_with_tuple<Condition, Default>
  {
    using lambda::with_tuple_type::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1>
  struct lambda<Condition, switch_action<Default, Case1>>
  : lambda_with_tuple<Condition, Default, Case1>
  {
    using lambda::with_tuple_type::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1, class Case2>
  struct lambda<Condition, switch_action<Default, Case1, Case2>>
  : lambda_with_tuple<Condition, Default, Case1, Case2>
  {
    using lambda_with_tuple<Condition, Default, Case1, Case2>::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1, class Case2, class Case3>
  struct lambda<Condition, switch_action<Default, Case1, Case2, Case3>>
  : lambda_with_tuple<Condition, Default, Case1, Case2, Case3>
  {
    using lambda_with_tuple<Condition, Default
    , Case1, Case2, Case3
    >::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        case Case3::value :
          std::get<4>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1
  , class Case2, class Case3, class Case4>
  struct lambda<Condition, switch_action<Default, Case1, Case2, Case3, Case4>>
  : lambda_with_tuple<Condition, Default, Case1, Case2, Case3, Case4>
  {
    using lambda_with_tuple<Condition, Default
    , Case1, Case2, Case3, Case4
    >::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        case Case3::value :
          std::get<4>(this->t)(std::forward<Args>(args)...);
          break;
        case Case4::value :
          std::get<5>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1
  , class Case2, class Case3, class Case4, class Case5>
  struct lambda<Condition, switch_action<Default, Case1, Case2, Case3, Case4, Case5>>
  : lambda_with_tuple<Condition, Default, Case1, Case2
  , Case3, Case4, Case5>
  {
    using lambda_with_tuple<Condition, Default
    , Case1, Case2, Case3, Case4, Case5
    >::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        case Case3::value :
          std::get<4>(this->t)(std::forward<Args>(args)...);
          break;
        case Case4::value :
          std::get<5>(this->t)(std::forward<Args>(args)...);
          break;
        case Case5::value :
          std::get<6>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1, class Case2
  , class Case3, class Case4, class Case5, class Case6>
  struct lambda<Condition, switch_action<Default, Case1, Case2, Case3
  , Case4, Case5, Case6>>
  : lambda_with_tuple<Condition, Default, Case1, Case2
  , Case3, Case4, Case5, Case6>
  {
    using lambda_with_tuple<Condition, Default
    , Case1, Case2, Case3, Case4, Case5, Case6
    >::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        case Case3::value :
          std::get<4>(this->t)(std::forward<Args>(args)...);
          break;
        case Case4::value :
          std::get<5>(this->t)(std::forward<Args>(args)...);
          break;
        case Case5::value :
          std::get<6>(this->t)(std::forward<Args>(args)...);
          break;
        case Case6::value :
          std::get<7>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1, class Case2
  , class Case3, class Case4, class Case5, class Case6, class Case7>
  struct lambda<Condition, switch_action<Default, Case1, Case2, Case3
  , Case4, Case5, Case6, Case7>>
  : lambda_with_tuple<Condition, Default, Case1, Case2
  , Case3, Case4, Case5, Case6, Case7>
  {
    using lambda_with_tuple<Condition, Default
    , Case1, Case2, Case3, Case4, Case5, Case6, Case7
    >::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        case Case3::value :
          std::get<4>(this->t)(std::forward<Args>(args)...);
          break;
        case Case4::value :
          std::get<5>(this->t)(std::forward<Args>(args)...);
          break;
        case Case5::value :
          std::get<6>(this->t)(std::forward<Args>(args)...);
          break;
        case Case6::value :
          std::get<7>(this->t)(std::forward<Args>(args)...);
          break;
        case Case7::value :
          std::get<8>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class Condition, class Default, class Case1, class Case2, class Case3
  , class Case4, class Case5, class Case6, class Case7, class Case8>
  struct lambda<Condition, switch_action<Default, Case1, Case2, Case3
  , Case4, Case5, Case6, Case7, Case8>>
  : lambda_with_tuple<Condition, Default, Case1, Case2
  , Case3, Case4, Case5, Case6, Case7, Case8>
  {
    using lambda_with_tuple<Condition, Default
    , Case1, Case2, Case3, Case4, Case5, Case6, Case7, Case8
    >::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      switch (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        case Case1::value :
          std::get<2>(this->t)(std::forward<Args>(args)...);
          break;
        case Case2::value :
          std::get<3>(this->t)(std::forward<Args>(args)...);
          break;
        case Case3::value :
          std::get<4>(this->t)(std::forward<Args>(args)...);
          break;
        case Case4::value :
          std::get<5>(this->t)(std::forward<Args>(args)...);
          break;
        case Case5::value :
          std::get<6>(this->t)(std::forward<Args>(args)...);
          break;
        case Case6::value :
          std::get<7>(this->t)(std::forward<Args>(args)...);
          break;
        case Case7::value :
          std::get<8>(this->t)(std::forward<Args>(args)...);
          break;
        case Case8::value :
          std::get<9>(this->t)(std::forward<Args>(args)...);
          break;
        default :
          std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

}

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Action7
, class Action8, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5, Action6, Action7, Action8>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, Action7 && act7, Action8 && act8, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
, std::forward<Action7>(act7)
, std::forward<Action8>(act8)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Action7
, class Action8, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5, Action6, Action7, Action8>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, Action7 && act7, Action8 && act8, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
, std::forward<Action7>(act7)
, std::forward<Action8>(act8)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Action7, class Action8>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default
, Action1, Action2, Action3, Action4, Action5, Action6, Action7, Action8>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, Action7 && act7, Action8 && act8)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
, std::forward<Action7>(act7)
, std::forward<Action8>(act8)
}; }


template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Action7, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5, Action6, Action7>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, Action7 && act7, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
, std::forward<Action7>(act7)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Action7, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5, Action6, Action7>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, Action7 && act7, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
, std::forward<Action7>(act7)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Action7>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default
, Action1, Action2, Action3, Action4, Action5, Action6, Action7>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, Action7 && act7)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
, std::forward<Action7>(act7)
}; }


template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5, Action6>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5, Action6>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Action6>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default
, Action1, Action2, Action3, Action4, Action5, Action6>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, Action6 && act6)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
, std::forward<Action6>(act6)
}; }


template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4, Action5>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5
, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Action5>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default
, Action1, Action2, Action3, Action4, Action5>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4, Action5 && act5)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
, std::forward<Action5>(act5)
}; }


template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4
, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default
, Action1, Action2, Action3, Action4>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4
, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
}; }

template<class Condition, class Action1, class Action2, class Action3
, class Action4>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default
, Action1, Action2, Action3, Action4>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, Action4 && act4)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
, std::forward<Action4>(act4)
}; }

template<class Condition, class Action1, class Action2, class Action3, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default, Action1, Action2, Action3>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
}; }

template<class Condition, class Action1, class Action2, class Action3, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default, Action1, Action2, Action3>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
}; }

template<class Condition, class Action1, class Action2, class Action3>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default
, Action1, Action2, Action3>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, Action3 && act3)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
, std::forward<Action3>(act3)
}; }

template<class Condition, class Action1, class Action2, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default, Action1, Action2>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
}; }

template<class Condition, class Action1, class Action2, class Default>
constexpr
_aux::lambda<Condition, _aux::switch_action<Default, Action1, Action2>>
switch_statement(Condition && cond
, Action1 && act1, Action2 && act2, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
}; }

template<class Condition, class Action1, class Action2>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default, Action1, Action2>>
switch_statement(Condition && cond, Action1 && act1, Action2 && act2)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
, std::forward<Action2>(act2)
}; }

template<class Condition, class Action1, class Default>
constexpr _aux::lambda<Condition, _aux::switch_action<Default, Action1>>
switch_statement(Condition && cond, Action1 && act1, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
}; }

template<class Condition, class Action1, class Default>
constexpr _aux::lambda<Condition, _aux::switch_action<Default, Action1>>
switch_statement(Condition && cond, Action1 && act1, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
, std::forward<Action1>(act1)
}; }

template<class Condition, class Action1>
constexpr
_aux::lambda<Condition, _aux::switch_action<_aux::switch_action_default, Action1>>
switch_statement(Condition && cond, Action1 && act1)
{ return {
  std::forward<Condition>(cond)
, _aux::switch_action_default()
, std::forward<Action1>(act1)
}; }

template<class Condition, class Default>
constexpr _aux::lambda<Condition, _aux::switch_action<Default>>
switch_statement(Condition && cond, _aux::case_default<Default> && def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
}; }

template<class Condition, class Default>
constexpr _aux::lambda<Condition, _aux::switch_action<Default>>
switch_statement(Condition && cond, _aux::case_default<Default> def)
{ return {
  std::forward<Condition>(cond)
, std::move(def)
}; }

template<long long Label, class Function>
constexpr _aux::case_action<Label, Function>
case_statement(Function && f)
{ return {std::forward<Function>(f)}; }

template<class Function>
constexpr _aux::case_default<Function>
default_statement(Function && f)
{ return {std::forward<Function>(f)}; }

}
}

#endif
