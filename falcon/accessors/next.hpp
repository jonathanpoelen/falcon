#ifndef FALCON_ACCESSOR_NEXT_HPP
#define FALCON_ACCESSOR_NEXT_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
# include <falcon/c++1x/syntax.hpp>
# include <utility>
#else
# include <falcon/type_traits/internal_reference.hpp>
#endif

namespace falcon {
namespace accessors {

namespace _aux {
  template<class T>
  struct result_next
  {
#if __cplusplus >= 201103L
    typedef decltype(std::declval<T&>().next()) type;
#else
    typedef typename ::falcon::internal_reference<T>::type;
#endif
  };
}

template <class T = void, class Result = void>
struct next
{
  typedef typename default_or_type<_aux::result_next<T>, Result, void>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR next() {}

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.next())
  { return x.next(); }
};

template<>
struct next<void, void>
{
  CPP_CONSTEXPR next() {}

  template<class T>
# if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T& x) const
  , x.next())
# else
  typename _aux::result_next<T>::type
  operator()(T& x) const
  { return x.next(); }
# endif
};

CPP_GLOBAL_CONSTEXPR next<> next_f;

}
}

#endif
