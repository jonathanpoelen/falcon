#ifndef FALCON_ACCESSOR_AT_HPP
#define FALCON_ACCESSOR_AT_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
# include <falcon/c++1x/syntax.hpp>
# include <utility>
#else
# include <falcon/detail/inner_reference.hpp>
#endif

#include <cstddef>

namespace falcon {
namespace accessors {

namespace _aux {
  template<class T, class Position>
  struct result_at
  {
    typedef
      CPP_IF_CPP1X(decltype(std::declval<T>().at(std::declval<Position>())))
      CPP_IF_NOT_CPP1X(typename __detail::inner_reference<T>::type)
    type;
  };
}

template <class T = void, class Position = void, class Result = void>
struct at
{
  typedef typename default_or_type<use<std::size_t>, Position, void>::type
    second_argument_type;
  typedef typename default_or_type<
    _aux::result_at<T, second_argument_type>, Result, void
  >::type result_type;
  typedef T first_argument_type;

  CPP_CONSTEXPR result_type operator()(T& cont, const second_argument_type& pos) const
  CPP_NOEXCEPT_OPERATOR2(cont.at(pos))
  { return cont.at(pos); }
};

template<>
struct at<void, void, void>
{
  template<class T, class Position>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T& cont, const Position& pos) const
  , cont.at(pos))
#else
  typename _aux::result_at<T, second_argument_type>::type
  operator()(T& cont, const Position& pos) const
  { return cont.at(pos); }
#endif
};

CPP_GLOBAL_CONSTEXPR at<> at_f;

}
}

#endif
