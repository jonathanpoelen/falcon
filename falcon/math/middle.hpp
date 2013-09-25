#ifndef FALCON_MATH_MIDDLE_HPP
#define FALCON_MATH_MIDDLE_HPP

#include <falcon/c++/constexpr.hpp>
#include <utility>

namespace falcon {
///middle operation without overflow
template <typename T>
CPP_CONSTEXPR T middle(const T& low, const T& high) {
	return low + (high - low) / 2;
}

///use middle<T>(@p a, @p b) if @p a less @p b, otherwise middle<T>(@p b, @p a)
template <typename T>
CPP_CONSTEXPR T safe_middle(const T& a, const T& b) {
	return a < b ? middle<T>(a, b) : middle<T>(b, a);
}

///middle<T>(@p p.first, @p p.second)
template <typename T>
inline CPP_CONSTEXPR T middle(const std::pair<T, T>& p) {
	return middle<T>(p.first, p.second);
}

///safe_middle<T>(@p p.first, @p p.second)
template <typename T>
inline CPP_CONSTEXPR T safe_middle(const std::pair<T, T>& p) {
	return safe_middle<T>(p.first, p.second);
}
}

#endif
