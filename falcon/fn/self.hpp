#ifndef FALCON_FN_SELF_HPP
#define FALCON_FN_SELF_HPP

#include <falcon/type_traits/static_const.hpp>
#include <utility>

namespace falcon {
namespace fn {

  struct self_fn {
    constexpr self_fn() noexcept {}

    template<class T>
    constexpr auto operator()(T&& x) const noexcept ->
    decltype(std::forward<T>(x))
    { return std::forward<T>(x); }
  };

  namespace  {
    constexpr auto const & self = static_const<self_fn>::value;
  }
}
}

#endif
