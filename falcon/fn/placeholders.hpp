#ifndef FALCON_FN_PLACEHOLDERS_HPP
#define FALCON_FN_PLACEHOLDERS_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/c++1x/syntax.hpp>
#include <tuple>

namespace falcon {
namespace fn {

  template<std::size_t I>
  struct placeholder {
    constexpr placeholder() noexcept {}

    template<class... Ts>
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
      operator()(Ts&&... args) const
    , std::get<I>(std::forward_as_tuple(std::forward<Ts>(args)...)))
  };

  namespace {
    constexpr auto const & _1 = static_const<placeholder<0>>::value;
    constexpr auto const & _2 = static_const<placeholder<1>>::value;
    constexpr auto const & _3 = static_const<placeholder<2>>::value;
    constexpr auto const & _4 = static_const<placeholder<3>>::value;
    constexpr auto const & _5 = static_const<placeholder<4>>::value;
    constexpr auto const & _6 = static_const<placeholder<5>>::value;
    constexpr auto const & _7 = static_const<placeholder<6>>::value;
    constexpr auto const & _8 = static_const<placeholder<7>>::value;
    constexpr auto const & _9 = static_const<placeholder<8>>::value;
    constexpr auto const & _10 = static_const<placeholder<9>>::value;
    constexpr auto const & _11 = static_const<placeholder<10>>::value;
    constexpr auto const & _12 = static_const<placeholder<11>>::value;
    constexpr auto const & _13 = static_const<placeholder<12>>::value;
    constexpr auto const & _14 = static_const<placeholder<13>>::value;
    constexpr auto const & _15 = static_const<placeholder<14>>::value;
  }
}
}

#endif
