#ifndef FALCON_ACCESSOR_BASE_HPP
#define FALCON_ACCESSOR_BASE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>

#include <falcon/type_traits/use.hpp>

#if __cplusplus >= 201103L
# include <utility>
#else
# include <boost/type_traits/conditional.hpp>
#endif

namespace falcon {
namespace accessors {

template <class T>
struct __result_base
{
  typedef
    CPP_IF_CPP1X(decltype(std::declval<T>().base()))
    CPP_IF_NOT_CPP1X(typename boost::remove_cv<T>::type::base_type)
  type;
};

template<class T CPP_IF_CPP1X(= void), class Result = use_default>
struct base_t
{
  typedef typename default_or_type<__result_base<T>, Result>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.base())
  { return x.base(); }
};

#if __cplusplus >= 201103L
template<>
struct base_t<void, use_default>
{
  template<class T>
  constexpr auto operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.base())
  -> decltype(x.base())
  { return x.base(); }
};

CPP_GLOBAL_CONSTEXPR base_t<> base;
#endif

}
}

#endif
