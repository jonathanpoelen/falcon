#ifndef FALCON_BIT_BACK_HPP
#define FALCON_BIT_BACK_HPP

#include <falcon/bit/size.hpp>

namespace falcon {
namespace bit {

///bit::size<_T>::value - 1
template <class T>
struct back
: integral_constant<T, size<T>::value - 1>
{};

}
}

#endif
