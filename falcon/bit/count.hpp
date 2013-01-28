#ifndef FALCON_BIT_COUNT_HPP
#define FALCON_BIT_COUNT_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace bit {

///count number of bits set in a byte
template<typename _T>
CPP_CONSTEXPR inline _T count(_T x)
{
	struct R { CPP_CONSTEXPR static inline _T r(_T y, _T count){
		return y ? r(y >> 1, count + (y & 1)) : count;
	} };
	return R::r(x >> 1, x & 1);
}

}
}

#endif