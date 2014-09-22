#ifndef FALCON_UTILITYTEMPORARY_SET_HPP
#define FALCON_UTILITYTEMPORARY_SET_HPP

#include <falcon/utility/move.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/functional/operators.hpp>
#if __cplusplus >= 201103L
# include <type_traits>
#endif

namespace falcon {

///\brief Modifies the value passed during the lifetime of the object
template<class T, class Assigner = assign<T, T> >
class temporary_set
{
  T * value_;
  T old_value_;
  Assigner assign_;

public:
  typedef T type;

public:
  template<class U>
  temporary_set(T& oldvalue_, U CPP_RVALUE_OR_CONST_REFERENCE newvalue_)
  : value_(&oldvalue_)
  , old_value_(FALCON_MOVE(oldvalue_))
  {
    assign_(*value_, FALCON_FORWARD(U, newvalue_));
  }

  template<class U>
  temporary_set(T& oldvalue_, U CPP_RVALUE_OR_CONST_REFERENCE newvalue_, Assigner fun)
  : value_(&oldvalue_)
  , old_value_(FALCON_MOVE(oldvalue_))
  , assign_(fun)
  {
    assign_(*value_, FALCON_FORWARD(U, newvalue_));
  }

#if __cplusplus >= 201103L
  temporary_set(temporary_set &&) = default;
  temporary_set(temporary_set const &) = delete;
  temporary_set& operator=(temporary_set &&) = default;
  temporary_set& operator=(temporary_set const &) = delete;
#endif

  ~temporary_set()
  {
    assign_(*value_, FALCON_MOVE(old_value_));
  }

  const T& old() const CPP_NOEXCEPT
  { return old_value_; }

  void old(const T & new_old)
  { old_value_ = new_old; }

#if __cplusplus >= 201103L
  void old(T && new_old)
  { old_value_ = std::move(new_old); }
#endif
};

///\brief make a temporary_set
template<class T, class U>
temporary_set<T>
temporary_value(T& oldvalue_, U CPP_RVALUE_OR_CONST_REFERENCE newvalue_)
{ return temporary_set<T>(oldvalue_,  FALCON_FORWARD(U, newvalue_)); }

template<class T, class U, class Assigner>
temporary_set<T, Assigner>
temporary_value(T& oldvalue_, U CPP_RVALUE_OR_CONST_REFERENCE newvalue_, Assigner CPP_RVALUE fun)
{ return temporary_set<T, Assigner>(oldvalue_
, FALCON_FORWARD(U, newvalue_), FALCON_FORWARD(Assigner, fun)); }

}

#endif
