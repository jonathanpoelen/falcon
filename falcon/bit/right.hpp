#ifndef FALCON_BIT_RIGHT_HPP
#define FALCON_BIT_RIGHT_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
namespace bit {

template<class T>
struct right
: integral_constant<T, 1>
{};

}
}

#endif
