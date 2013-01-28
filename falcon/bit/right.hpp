#ifndef _FALCON_BIT_RIGHT_HPP
#define _FALCON_BIT_RIGHT_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
namespace bit {

template<typename _T>
struct right
: integral_constant<_T, 1>
{};

}
}

#endif