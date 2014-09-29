#ifndef FALCON_BIT_COUNT_HPP
#define FALCON_BIT_COUNT_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {
namespace bit {

namespace aux_ {
  struct count_impl {
    template<class T>
    CPP_CONSTEXPR static T
    impl(T y, T count) CPP_NOEXCEPT {
      return y ? impl(y >> 1, count + (y & 1)) : count;
    }
  };
}

///count number of bits set in a byte
template<class T>
CPP_CONSTEXPR T count(T x) CPP_NOEXCEPT
{ return aux_::count_impl::impl(x >> 1, x & 1); }

}
}

#endif
