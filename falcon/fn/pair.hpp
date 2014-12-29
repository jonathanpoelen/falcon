#ifndef FALCON_FN_PAIR_HPP
#define FALCON_FN_PAIR_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/tuple/get.hpp>
#include <utility>

namespace falcon {
namespace fn {

  namespace adl_
  {
    template<class P>
    constexpr auto first(P && p) noexcept ->
    decltype(get<0>(std::forward<P>(p)))
    { return get<0>(std::forward<P>(p)); }

    template<class P>
    constexpr auto second(P && p) noexcept ->
    decltype(get<1>(std::forward<P>(p)))
    { return get<1>(std::forward<P>(p)); }


    struct first_fn
    {
      constexpr first_fn() noexcept {}

      template<class T>
      constexpr auto operator()(T && x) const ->
      decltype(first(std::forward<T>(x)))
      { return first(std::forward<T>(x)); }
    };

    struct second_fn
    {
      constexpr second_fn() noexcept {}

      template<class T>
      constexpr auto operator()(T && x) const ->
      decltype(second(std::forward<T>(x)))
      { return second(std::forward<T>(x)); }
    };
  }

  /// \brief call get< 0>(T)
  typedef adl_::first_fn first_fn;
  /// \brief call get< 1>(T)
  typedef adl_::second_fn second_fn;

  namespace {
    constexpr auto const & first = static_const<first_fn>::value;
    constexpr auto const & second = static_const<second_fn>::value;
  }
}
}

#endif
