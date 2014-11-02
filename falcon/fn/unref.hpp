#ifndef FALCON_FN_UNREF_HPP
#define FALCON_FN_UNREF_HPP

#include <falcon/type_traits/static_const.hpp>
#include <utility>

namespace falcon {
namespace fn {

  struct unref_fn {
    constexpr unref_fn() noexcept {}

    template<class T>
    constexpr T operator()(T const & x) const
    { return x; }

    template<class T>
    constexpr T operator()(T && x) const
    { return std::move(x); }
  };

  namespace  {
    constexpr auto const & unref = static_const<unref_fn>::value;
  }
}
}

#endif
