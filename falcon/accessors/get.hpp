#ifndef FALCON_ACCESSOR_GET_HPP
#define FALCON_ACCESSOR_GET_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
# include <falcon/c++1x/syntax.hpp>
# include <utility>
#else
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/conditional.hpp>
#endif

namespace falcon {
namespace accessors {

namespace _aux {
  template <class T>
  struct result_get
  {
#if __cplusplus >= 201103L
    typedef decltype(std::declval<T>().get()) type;
#else
    typedef typename boost::remove_cv<T>::type::type& __type;
    typedef typename boost::conditional<
      boost::is_const<T>::value, const __type &, __type &
    >::type type;
#endif
  };
}

template <class T = void, class Result = void>
struct get
{
  typedef typename default_or_type<_aux::result_get<T>, Result, void>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.get())
  { return x.get(); }
};

template<>
struct get<void, void>
{
  template<class T>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T& x) const
  , x.get())
#else
  typename _aux::result_get<T>::type
  operator()(T& x) const
  { return x.get(); }
#endif
};

CPP_GLOBAL_CONSTEXPR get<> get_f;

}
}

#endif
