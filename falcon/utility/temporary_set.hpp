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
template<class T, class Assigner = affect<T, T> >
class temporary_set
{
  T * _value;
  T _old_value;
  Assigner _assign;

public:
  typedef T type;

public:
  template<class U>
  temporary_set(T& old_value, U CPP_RVALUE_OR_CONST_REFERENCE new_value)
  : _value(&old_value)
  , _old_value(FALCON_MOVE(old_value))
  {
    _assign(*_value, FALCON_FORWARD(U, new_value));
  }

  template<class U>
  temporary_set(T& old_value, U CPP_RVALUE_OR_CONST_REFERENCE new_value, Assigner fun)
  : _value(&old_value)
  , _old_value(FALCON_MOVE(old_value))
  , _assign(fun)
  {
    _assign(*_value, FALCON_FORWARD(U, new_value));
  }

#if __cplusplus >= 201103L
  temporary_set(temporary_set &&) = default;
  temporary_set(temporary_set const &) = delete;
  temporary_set& operator=(temporary_set &&) = default;
  temporary_set& operator=(temporary_set const &) = delete;
#endif

  ~temporary_set()
  {
    _assign(*_value, FALCON_MOVE(_old_value));
  }

  const T& old() const CPP_NOEXCEPT
  { return _old_value; }

  void old(const T & new_old)
  { _old_value = new_old; }

#if __cplusplus >= 201103L
  void old(T && new_old)
  { _old_value = std::move(new_old); }
#endif
};

///\brief make a temporary_set
template<class T, class U>
temporary_set<T>
temporary_value(T& old_value, U CPP_RVALUE_OR_CONST_REFERENCE new_value)
{ return temporary_set<T>(old_value,  FALCON_FORWARD(U, new_value)); }

template<class T, class U, class Assigner>
temporary_set<T, Assigner>
temporary_value(T& old_value, U CPP_RVALUE_OR_CONST_REFERENCE new_value, Assigner CPP_RVALUE fun)
{ return temporary_set<T, Assigner>(old_value
, FALCON_FORWARD(U, new_value), FALCON_FORWARD(Assigner, fun)); }

}

#endif
