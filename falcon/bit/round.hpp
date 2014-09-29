#ifndef FALCON_BIT_ROUND_HPP
#define FALCON_BIT_ROUND_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {
namespace bit {

namespace aux_ {
  struct round_impl {
    template<class T>
    CPP_CONSTEXPR static T
    impl(T y) CPP_NOEXCEPT {
      return y & (y - 1) ? impl(y & (y - 1)) : y << 1;
    }
  };
}
/**
 * round up to next highest single bit:
 * round(15) == 16, round(16) == 16, round(17) == 32
 */
template<class T>
CPP_CONSTEXPR T round(T x) CPP_NOEXCEPT
{ return x & (x - 1) ? aux_::round_impl::impl(x) : x; }

}
}

#endif
