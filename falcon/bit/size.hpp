#ifndef _FALCON_BIT_SIZE_HPP
#define _FALCON_BIT_SIZE_HPP

#include <cstddef>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
namespace bit {

template <typename _T>
struct size
: integral_constant<std::size_t, __CHAR_BIT__ * sizeof(_T)>
{};

}
}

#endif