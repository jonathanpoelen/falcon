#ifndef FALCON_FUNCTIONAL_STORE_IF_HPP
#define FALCON_FUNCTIONAL_STORE_IF_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/cast/static_caster.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_pointer)

namespace falcon {

/**
 * \tparam TOrUnary must be a pointer type or a unary functor
 */
template <
  class TOrUnary
, class Predicate = static_caster<bool>
, bool IsNot = false
>
struct __store_if
{
  typedef TOrUnary type;


  __store_if(TOrUnary x, Predicate tester)
  : _val(x)
  , _test(tester)
  {}

  __store_if(Predicate tester)
  : _test(tester)
  {}

  __store_if(TOrUnary x)
  : _val(x)
  {}

#if __cplusplus >= 201103L
  __store_if() = default;
# else
  __store_if() {}
#endif

  template<class U>
  bool operator()(U CPP_RVALUE_OR_CONST_REFERENCE x) const
  {
    if (bool(_test(static_cast<const U&>(x))) != IsNot)
    {
      clear(FALCON_FORWARD(U, x));
      return true;
    }
    return false;
  }

    TOrUnary& get()
  { return _val; }

  const TOrUnary& get() const
  { return _val; }

  template<class U>
  void clear(U CPP_RVALUE_OR_CONST_REFERENCE x) const
  {
    using FALCON_BOOST_OR_STD_NAMESPACE::is_pointer;
    assign_val(_val, FALCON_FORWARD(U, x), typename is_pointer<TOrUnary>::type());
  }

private:
  template<class P, class U>
  static void assign_val(P * x, U CPP_RVALUE_OR_CONST_REFERENCE y, true_type)
  { *x = FALCON_FORWARD(U, y); }

  template<class U>
  static void
  assign_val(TOrUnary const & x, U CPP_RVALUE_OR_CONST_REFERENCE y, false_type)
  { x(FALCON_FORWARD(U, y)); }

  TOrUnary _val;
  Predicate _test;
};

#if __cplusplus >= 201103L
template <
  class TOrUnary
, class Predicate = static_caster<bool>
>
using store_if = __store_if<TOrUnary, Predicate>;

template <
  class TOrUnary
, class Predicate = static_caster<bool>
>
using store_if_not = __store_if<TOrUnary, Predicate, true>;
#else
template <
  typename TOrUnary,
  typename Predicate = static_caster<bool>,
>
struct store_if
: __store_if<TOrUnary, Predicate>
{
private:
  typedef __store_if<TOrUnary, Predicate> __base;

public:
  store_if(const TOrUnary & p, Predicate tester)
  : __base(tester, p)
  {}

  store_if(Predicate tester)
  : __base(tester, p)
  {}

  store_if(const TOrUnary & p)
  : __base(p)
  {}

  store_if()
  {}
};

template <
  typename TOrUnary,
  typename Predicate = static_caster<bool>
>
struct store_if_not
: __store_if<TOrUnary, Predicate, true>
{
private:
  typedef __store_if<TOrUnary, Predicate, true> __base;

public:
  store_if_not(const TOrUnary & p, Predicate tester)
  : __base(tester, assignval, p)
  {}

  store_if_not(Predicate tester)
  : __base(tester, p)
  {}

  store_if_not(const TOrUnary & p)
  : __base(p)
  {}

  store_if_not()
  {}
};
#endif

template<class TOrUnary, class Predicate>
store_if<TOrUnary, Predicate> make_store_if(
  TOrUnary CPP_RVALUE_OR_CONST_REFERENCE x
, Predicate CPP_RVALUE_OR_CONST_REFERENCE test
) {
  return store_if<TOrUnary, Predicate>(
    FALCON_FORWARD(TOrUnary, x)
  , FALCON_FORWARD(Predicate, test)
  );
}

}

#endif
