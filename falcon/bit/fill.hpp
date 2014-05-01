#ifndef FALCON_BIT_FILL_HPP
#define FALCON_BIT_FILL_HPP

#include <falcon/bit/size.hpp>

namespace falcon {
namespace bit {

template <class T, std::size_t NRight = size<T>::value>
struct fill
: integral_constant<T, (T(~0LL) >> (size<T>::value - NRight))>
{};

}
}

#endif
