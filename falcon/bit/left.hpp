#ifndef FALCON_BIT_LEFT_HPP
#define FALCON_BIT_LEFT_HPP

#include <falcon/bit/size.hpp>

namespace falcon {
namespace bit {

template<class T>
struct left
: integral_constant<T, T(T(1) << (size<T>::value - 1))>
{};

}
}

#endif
