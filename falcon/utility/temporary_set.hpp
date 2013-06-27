#ifndef FALCON_UTILITYTEMPORARY_SET_HPP
#define FALCON_UTILITYTEMPORARY_SET_HPP

#include <falcon/utility/move.hpp>
#include <falcon/c++/reference.hpp>

namespace falcon {

///\brief Modifies the value passed during the lifetime of the object
template<typename T>
class temporary_set
{
  T& _value;
  T _old_value;

public:
  typedef T type;

public:
  temporary_set(T& old_value, T CPP_RVALUE_OR_CONST_REFERENCE new_value)
  : _value(old_value)
  , _old_value(FALCON_MOVE(old_value))
  {
    _value = FALCON_FORWARD(T, new_value);
  }

  ~temporary_set()
  {
    _value = FALCON_FORWARD(T, _old_value);
  }

  const T& old() const
  { return _old_value; }
};

///\brief make a temporary_set
template<typename T>
temporary_set<T> temporary_value(T& old_value, T CPP_RVALUE_OR_CONST_REFERENCE new_value)
{ return temporary_set<T>(old_value, FALCON_FORWARD(T, new_value)); }

}

#endif
