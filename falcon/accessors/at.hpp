#ifndef FALCON_ACCESSOR_AT_HPP
#define FALCON_ACCESSOR_AT_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/type_traits/use.hpp>

#if __cplusplus >= 201103L
# include <utility>
#else
# include <falcon/detail/inner_reference.hpp>
#endif

#include <cstddef>

namespace falcon {
namespace accessors {

template<class T, class Position>
struct __result_at
{
  typedef
    CPP_IF_CPP1X(decltype(std::declval<T>().at(std::declval<Position>())))
    CPP_IF_NOT_CPP1X(typename __detail::inner_reference<T>::type)
  type;
};

template <class T CPP_IF_CPP1X(= void)
, class Position = use_default, class Result = use_default>
struct at_t
{
  typedef typename default_or_type<use<std::size_t>, Position>::type
    second_argument_type;
  typedef typename default_or_type<__result_at<T, second_argument_type>, Result>::type
    result_type;
  typedef T first_argument_type;

  CPP_CONSTEXPR result_type operator()(T& cont, const second_argument_type& pos) const
  CPP_NOEXCEPT_OPERATOR2(cont.at(pos))
  { return cont.at(pos); }
};

#if __cplusplus >= 201103L
template<>
struct at_t<void, use_default, use_default>
{
  template<class T, class Position>
  constexpr auto operator()(T& cont, const Position& pos) const
  CPP_NOEXCEPT_OPERATOR2(cont.at(pos))
  -> decltype(cont.at(pos))
  { return cont.at(pos); }
};

CPP_GLOBAL_CONSTEXPR at_t<> at;
#endif

}
}

#endif
