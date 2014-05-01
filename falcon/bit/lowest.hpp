#ifndef FALCON_BIT_LOWEST_HPP
#define FALCON_BIT_LOWEST_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {
namespace bit {

///lowest_bit(0b1110) == 0b0010
template<typename T>
CPP_CONSTEXPR T lowest(T x) CPP_NOEXCEPT
{ return static_cast<T>(x & -x); }

///clear_lowest_bit(0b1110) == 0b1100
template<typename T>
CPP_CONSTEXPR T clear_lowest(T x) CPP_NOEXCEPT
{ return static_cast<T>(x & (x - 1)); }

///insert_lowest_bit(0b0101) == 0b0111
template<typename T>
CPP_CONSTEXPR T insert_lowest(T x) CPP_NOEXCEPT
{ return static_cast<T>(x | (x + 1)); }

}
}

#endif
