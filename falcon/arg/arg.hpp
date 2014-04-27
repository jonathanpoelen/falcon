#ifndef FALCON_ARG_ARG_HPP
#define FALCON_ARG_ARG_HPP

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
    { return arg<I-1, Result>::get(args...); }
  };

  template<class Result>
  struct arg<0, Result>
  {
    template<class T, class... Args>
    static constexpr Result get(T&& a, Args&&...)
    { return a; }
  };
}

template<std::size_t I, class... Args>
constexpr typename arg_element<I, Args...>::type arg(Args&&... args)
{
  return _aux::arg<I, typename arg_element<I, Args...>::type>
    ::get(std::forward<Args>(args)...);
}

}

#endif
