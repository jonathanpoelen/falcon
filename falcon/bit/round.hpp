#ifndef FALCON_BIT_ROUND_HPP
#define FALCON_BIT_ROUND_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {
namespace bit {

/**
 * round up to next highest single bit:
 * round(15) == 16, round(16) == 16, round(17) == 32
 */
template<class T>
CPP_CONSTEXPR T round(T x) CPP_NOEXCEPT
{
  struct R { CPP_CONSTEXPR static T
  r(T y) CPP_NOEXCEPT {
		return y & (y - 1) ? r(y & (y - 1)) : y << 1;
	} };
	return x & (x - 1) ? R::r(x) : x;
}

}
}

#endif
