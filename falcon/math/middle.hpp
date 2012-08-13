#ifndef _FALCON_MATH_MIDDLE_HPP
#define _FALCON_MATH_MIDDLE_HPP

#include <utility>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
///middle operation without overflow
template <typename _T>
CPP_CONSTEXPR _T middle(const _T& low, const _T& high) {
	return low + (high - low) / 2;
}

///use middle<_T>(@p a, @p b) if @p a less @p b, otherwise middle<_T>(@p b, @p a)
template <typename _T>
CPP_CONSTEXPR _T safe_middle(const _T& a, const _T& b) {
	return a < b ? middle<_T>(a, b) : middle<_T>(b, a);
}

///middle<_T>(@p p.first, @p p.second)
template <typename _T>
inline CPP_CONSTEXPR _T middle(const std::pair<_T, _T>& p) {
	return middle<_T>(p.first, p.second);
}

///safe_middle<_T>(@p p.first, @p p.second)
template <typename _T>
inline CPP_CONSTEXPR _T safe_middle(const std::pair<_T, _T>& p) {
	return safe_middle<_T>(p.first, p.second);
}
}

#endif
