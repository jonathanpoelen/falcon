#ifndef FALCON_FUNCTIONAL_ARG_HPP
#define FALCON_FUNCTIONAL_ARG_HPP

#include <falcon/parameter/parameter_element.hpp>
#include <type_traits>
#include <utility>

namespace falcon {

template <class... Args>
struct arg_size
: std::integral_constant<std::size_t, sizeof...(Args)>
{};

template <std::size_t I, class... Args>
struct arg_element
{ typedef typename parameter_element<I, parameter_pack<Args...>>::type type; };

namespace _aux {
  template<std::size_t I, class Result>
  struct arg
  {
    template<class T, class... Args>
    static constexpr Result get(T&&, Args&&... args)
    { return arg<I-1, Result>::get(std::forward<Args>(args)...); }
  };

  template<class Result>
  struct arg<0, Result>
  {
    template<class T, class... Args>
    static constexpr Result get(T&& a, Args&&...)
    { return std::forward<T>(a); }
  };

  template<class T>
  struct arg_result
  { typedef T&& type; };

  template<class T>
  struct arg_result<T&>
  { typedef T& type; };
}

template<std::size_t I, class... Args>
constexpr typename _aux::arg_result<
  typename arg_element<I, Args...>::type
>::type arg(Args&&... args)
{
  return _aux::arg<I, typename _aux::arg_result<
    typename arg_element<I, Args...>::type
  >::type>::get(std::forward<Args>(args)...);
}

}

#endif
