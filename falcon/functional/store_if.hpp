#ifndef FALCON_FUNCTIONAL_STORE_IF_HPP
#define FALCON_FUNCTIONAL_STORE_IF_HPP

#include <falcon/cast/static_caster.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>

namespace falcon {

struct __store_if_set_value
{
  template <typename T, typename U>
#if __cplusplus >= 201103L
  void operator()(const T & x, U && y) const
  { x = std::forward<U>(y); }
#else
  void operator()(const T & x, U & y) const
  { x = y; }
#endif

  template <typename T, typename U>
  void operator()(T * x, U & y) const
  { *x = y; }

  template <typename T, typename U>
  void operator()(T * x, U * y) const
  { *x = *y; }
};

template <
  typename T,
  typename Functor = static_caster<bool>,
  typename AssignVal = __store_if_set_value,
  bool IsNot = false
>
class __store_if
{
public:
  typedef T type;
  typedef Functor functor_type;
  typedef AssignVal accessor_type;

private:
  Functor _functor;
  AssignVal _set_val;
  T _marchandise;

public:
  __store_if(Functor CPP_RVALUE_OR_CONST_REFERENCE functor,
             AssignVal CPP_RVALUE_OR_CONST_REFERENCE access,
             T CPP_RVALUE_OR_CONST_REFERENCE value)
  : _functor(FALCON_FORWARD(Functor, functor))
  , _set_val(FALCON_FORWARD(AssignVal, access))
  , _marchandise(FALCON_FORWARD(T, value))
  {}

  __store_if(Functor CPP_RVALUE_OR_CONST_REFERENCE functor,
             AssignVal CPP_RVALUE_OR_CONST_REFERENCE access)
  : _functor(FALCON_FORWARD(Functor, functor))
  , _set_val(FALCON_FORWARD(AssignVal, access))
  , _marchandise()
  {}

  __store_if(Functor CPP_RVALUE_OR_CONST_REFERENCE functor,
             T CPP_RVALUE_OR_CONST_REFERENCE value)
  : _functor(FALCON_FORWARD(Functor, functor))
  , _set_val()
  , _marchandise(FALCON_FORWARD(T, value))
  {}

  __store_if(Functor CPP_RVALUE_OR_CONST_REFERENCE functor)
  : _functor(FALCON_FORWARD(Functor, functor))
  , _set_val()
  , _marchandise()
  {}

  __store_if(T CPP_RVALUE_OR_CONST_REFERENCE value)
  : _functor()
  , _set_val()
  , _marchandise(FALCON_FORWARD(T, value))
  {}

  __store_if()
  : _functor()
  , _set_val()
  , _marchandise()
  {}

  template<typename _U>
  bool operator()(_U& value) const
  {
    if (IsNot ? !_functor(value) : _functor(value))
    {
      _set_val(_marchandise, value);
      return true;
    }
    return false;
  }

  T& get()
  { return _marchandise; }

  const T& get() const
  { return _marchandise; }

  void set(T CPP_RVALUE_OR_CONST_REFERENCE value)
  { _marchandise = FALCON_FORWARD(T, value); }

  void clear()
  { _marchandise = T(); }
};

#if __cplusplus >= 201103L
template <
  typename T,
  typename Functor = static_caster<bool>,
  typename AssignVal = __store_if_set_value
>
using store_if = __store_if<T, Functor, AssignVal>;

template <
  typename T,
  typename Functor = static_caster<bool>,
  typename AssignVal = __store_if_set_value
>
using store_if_not = __store_if<T, Functor, AssignVal, true>;
#else
template <
  typename T,
  typename Functor = static_caster<bool>,
  typename AssignVal = __store_if_set_value
>
struct store_if
: __store_if<T, Functor, AssignVal>
{
private:
  typedef __store_if<T, Functor, AssignVal> __base;

public:
  store_if(Functor functor, AssignVal access, const T & p = T())
  : __base(functor, access, p)
  {}

  store_if(Functor functor, const T & p = T())
  : __base(functor, p)
  {}

  store_if(const T & p = T())
  : __base(p)
  {}
};

template <
  typename T,
  typename Functor = static_caster<bool>,
  typename AssignVal = __store_if_set_value
>
struct store_if_not
: __store_if<T, Functor, AssignVal, true>
{
private:
  typedef __store_if<T, Functor, AssignVal, true> __base;

public:
  store_if_not(Functor functor, AssignVal access, const T & p = T())
  : __base(functor, access, p)
  {}

  store_if_not(Functor functor, const T & p = T())
  : __base(functor, p)
  {}

  store_if_not(const T & p = T())
  : __base(p)
  {}
};
#endif

}

#endif
