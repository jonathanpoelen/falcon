#ifndef FALCON_ACCESSOR_BASE_HPP
#define FALCON_ACCESSOR_BASE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>

#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
# include <utility>
# include <falcon/c++1x/syntax.hpp>
#else
# include <falcon/type_traits/enable_type.hpp>
#endif

namespace falcon {
namespace accessors {

namespace _aux {
#if __cplusplus >= 201103L
  template <class T>
  struct result_base
  { typedef decltype(std::declval<T&>().base()) type; };
#else
  template <
    class T
  , class U = typename boost::remove_cv<T>::type::base_type
  , typename Enable = void>
  struct result_base
  { typedef U::iterator_type type; };

  template <class T, class U>
  struct result_base<T, U, typename ::falcon::enable_type<typename U::base_type>::type>
  { typedef typename T::base_type type; };
#endif
}

template<class T = void, class Result = void>
struct base
{
  typedef typename default_or_type<_aux::result_base<T>, Result, void>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.base())
  { return x.base(); }
};

template<>
struct base<void, void>
{
  template<class T>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T& x) const
  , x.base())
#else
  typename _aux::result_base<T>::type
  operator()(T& x) const
  { return x.base(); }
#endif
};

CPP_GLOBAL_CONSTEXPR base<> base_f;

}
}

#endif
