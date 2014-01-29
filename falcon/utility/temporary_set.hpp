#ifndef FALCON_UTILITYTEMPORARY_SET_HPP
#define FALCON_UTILITYTEMPORARY_SET_HPP

#include <falcon/utility/move.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/functional/operators.hpp>

namespace falcon {

///\brief Modifies the value passed during the lifetime of the object
template<class T, class U = T, class Assigner = affect<T, U> >
class temporary_set
{
  T * _value;
  U _old_value;
  Assigner _assign;

public:
  typedef T type;

public:
  template<class UU>
  temporary_set(T& old_value, UU CPP_RVALUE_OR_CONST_REFERENCE new_value)
  : _value(&old_value)
  , _old_value(FALCON_MOVE(old_value))
  {
    _assign(*_value, FALCON_FORWARD(UU, new_value));
  }

  template<class UU, class TAssigner>
  temporary_set(T& old_value, UU CPP_RVALUE_OR_CONST_REFERENCE new_value,
                TAssigner CPP_RVALUE_OR_CONST_REFERENCE fun)
  : _value(&old_value)
  , _old_value(FALCON_MOVE(old_value))
  , _assign(FALCON_FORWARD(TAssigner, fun))
  {
    _assign(*_value, FALCON_FORWARD(UU, new_value));
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
temporary_set<T, U>
temporary_value(T& old_value, U CPP_RVALUE_OR_CONST_REFERENCE new_value)
{ return temporary_set<T, U>(old_value, FALCON_FORWARD(U, new_value)); }

template<class T, class U, class Assigner>
temporary_set<T, U, Assigner>
temporary_value(T& old_value, U CPP_RVALUE_OR_CONST_REFERENCE new_value, Assigner fun)
{ return temporary_set<T, U>(old_value, FALCON_FORWARD(U, new_value), fun); }

}

#endif
