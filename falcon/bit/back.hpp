#ifndef _FALCON_BIT_BACK_HPP
#define _FALCON_BIT_BACK_HPP

#include <falcon/bit/size.hpp>

namespace falcon {
namespace bit {

///bit::size<_T>::value - 1
template <typename _T, typename _Result = unsigned>
struct back
: integral_constant<_Result, size<_T>::value - 1>
{};

}
}

#endif