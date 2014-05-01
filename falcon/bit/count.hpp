#ifndef FALCON_BIT_COUNT_HPP
#define FALCON_BIT_COUNT_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {
namespace bit {

///count number of bits set in a byte
template<class T>
CPP_CONSTEXPR T count(T x) CPP_NOEXCEPT
{
  struct R { CPP_CONSTEXPR static T
  r(T y, T count) CPP_NOEXCEPT {
		return y ? r(y >> 1, count + (y & 1)) : count;
	} };
	return R::r(x >> 1, x & 1);
}

}
}

#endif
