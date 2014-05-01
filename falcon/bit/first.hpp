#ifndef FALCON_BIT_FIRST_HPP
#define FALCON_BIT_FIRST_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/bit/edge.hpp>

namespace falcon {
namespace bit {

template <typename T>
CPP_CONSTEXPR T first(T d) CPP_NOEXCEPT
{
	struct R { CPP_CONSTEXPR static T
	r(T x, T dd = right<T>::value >> 1) CPP_NOEXCEPT {
		return dd < x ? r(dd << 1) : dd >> 1;
	} };
	return !d ? left<T>::value
	: (d == right<T>::value ? d : R::r(d));
}

}
}

#endif
