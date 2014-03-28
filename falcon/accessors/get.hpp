#ifndef FALCON_ACCESSOR_GET_HPP
#define FALCON_ACCESSOR_GET_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/type_traits/use.hpp>

#if __cplusplus >= 201103L
# include <utility>
#else
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/conditional.hpp>
#endif

namespace falcon {
namespace accessors {

template <class T>
struct __result_get
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

template <class T CPP_IF_CPP1X(= void), class Result = use_default>
struct get_t
{
  typedef typename default_or_type<__result_get<T>, Result>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.get())
  { return x.get(); }
};

#if __cplusplus >= 201103L
template<>
struct get_t<void>
{
  template<class T>
  constexpr auto operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.get())
  -> decltype(x.get())
  { return x.get(); }
};

CPP_GLOBAL_CONSTEXPR get_t<> get;
#endif

}
}

#endif
