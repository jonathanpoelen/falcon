#ifndef _FALCON_BIT_FILL_HPP
#define _FALCON_BIT_FILL_HPP

#include <falcon/bit/size.hpp>

namespace falcon {
namespace bit {

template <typename _T, std::size_t _NRight = size<_T>::value>
struct fill
: integral_constant<_T, (_T(~0LL) >> (size<_T>::value - _NRight))>
{};

}
}

#endif