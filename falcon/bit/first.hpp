#ifndef _FALCON_BIT_FIRST_HPP
#define _FALCON_BIT_FIRST_HPP

#include <falcon/bit/edge.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace bit {

template <typename _T>
CPP_CONSTEXPR inline _T first(_T d)
{
	struct R { CPP_CONSTEXPR static inline _T
	r(_T x, _T dd = right<_T>::value >> 1){
		return dd < x ? r(dd << 1) : dd >> 1;
	} };
	return !d ? left<_T>::value
	: (d == right<_T>::value ? d : R::r(d));
}

}
}

#endif