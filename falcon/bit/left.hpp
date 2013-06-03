#ifndef _FALCON_BIT_LEFT_HPP
#define _FALCON_BIT_LEFT_HPP

#include <falcon/bit/size.hpp>

namespace falcon {
namespace bit {

template<typename _T>
struct left
: integral_constant<_T, _T(_T(1) << (size<_T>::value - 1))>
{};

}
}

#endif
