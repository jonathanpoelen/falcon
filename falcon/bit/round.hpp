#ifndef FALCON_BIT_ROUND_HPP
#define FALCON_BIT_ROUND_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace bit {

/**
 * round up to next highest single bit:
 * round(15) == 16, round(16) == 16, round(17) == 32
 */
template<typename _T>
CPP_CONSTEXPR inline _T round(_T x)
{
	struct R { CPP_CONSTEXPR static inline _T r(_T y) {
		return y & (y - 1) ? r(y & (y - 1)) : y << 1;
	} };
	return x & (x - 1) ? R::r(x) : x;
}

}
}

#endif