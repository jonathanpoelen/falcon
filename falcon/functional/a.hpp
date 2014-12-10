#ifndef FALCON_FUNCTIONAL_A_HPP
#define FALCON_FUNCTIONAL_A_HPP

#include <falcon/type_traits/normalize_index.hpp>
#include <falcon/type_traits/static_const.hpp>
#include <falcon/functional/arg.hpp>
#include <falcon/c++1x/syntax.hpp>


namespace falcon {

/// \brief wrapper for arg< I>(args...)
template<unormalized_index_t I>
struct a {
  constexpr a() noexcept {}

  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts&&... args) const
  , arg<
    (normalize_index<I, sizeof...(args)>::value)
  >(std::forward<Ts>(args)...))
};

namespace {
  constexpr auto const & a0 = static_const<a<0>>::value;
  constexpr auto const & a1 = static_const<a<1>>::value;
  constexpr auto const & a2 = static_const<a<2>>::value;
  constexpr auto const & a3 = static_const<a<3>>::value;
  constexpr auto const & a4 = static_const<a<4>>::value;
  constexpr auto const & a5 = static_const<a<5>>::value;
  constexpr auto const & a6 = static_const<a<6>>::value;
  constexpr auto const & a7 = static_const<a<7>>::value;
  constexpr auto const & a8 = static_const<a<8>>::value;
  constexpr auto const & a9 = static_const<a<9>>::value;
  constexpr auto const & a10 = static_const<a<10>>::value;
  constexpr auto const & a11 = static_const<a<11>>::value;
  constexpr auto const & a12 = static_const<a<12>>::value;
  constexpr auto const & a13 = static_const<a<13>>::value;
  constexpr auto const & a14 = static_const<a<14>>::value;
  constexpr auto const & a15 = static_const<a<15>>::value;

  constexpr auto const & alast = static_const<a<(-1)>>::value;
}

}

#endif
