#ifndef FALCON_BIT_LOWEST_HPP
#define FALCON_BIT_LOWEST_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace bit {

///lowest_bit(0b1110) == 0b0010
template<typename _T>
CPP_CONSTEXPR inline _T lowest(_T x)
{ return static_cast<_T>(x & -x); }

///clear_lowest_bit(0b1110) == 0b1100
template<typename _T>
CPP_CONSTEXPR inline _T clear_lowest(_T x)
{ return static_cast<_T>(x & (x - 1)); }

///insert_lowest_bit(0b0101) == 0b0111
template<typename _T>
CPP_CONSTEXPR inline _T insert_lowest(_T x)
{ return static_cast<_T>(x | (x + 1)); }

}
}

#endif