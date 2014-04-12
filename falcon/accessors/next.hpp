#ifndef FALCON_ACCESSOR_NEXT_HPP
#define FALCON_ACCESSOR_NEXT_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
# include <utility>
#else
# include <falcon/detail/inner_reference.hpp>
#endif

namespace falcon {
namespace accessors {

template<class T>
struct __result_next
{
#if __cplusplus >= 201103L
  typedef decltype(std::declval<T>().next()) type;
#else
  typedef typename __detail::inner_reference<T>::type type;
#endif
};

template <class T CPP_IF_CPP1X(= void), class Result = use_default>
struct next
{
  typedef typename default_or_type<__result_next<T>, Result>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.next())
  { return x.next(); }
};

#if __cplusplus >= 201103L
template<>
struct next<void, use_default>
{
  template<class T>
  constexpr auto operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.next())
  -> decltype(x.next())
  { return x.next(); }
};

CPP_GLOBAL_CONSTEXPR next<> next_f;
#endif

}
}

#endif
