#ifndef FALCON_BIT_BYTE_CAST_HPP
#define FALCON_BIT_BYTE_CAST_HPP

#include <falcon/c++/noexcept.hpp>
#include <cstddef>

namespace falcon {

typedef unsigned char byte_t;

inline byte_t * byte_cast(void * p) CPP_NOEXCEPT
{ return reinterpret_cast<byte_t*>(p); }

inline std::ptrdiff_t byte_distance(void * p1, void * p2) CPP_NOEXCEPT
{ return reinterpret_cast<byte_t*>(p2) - reinterpret_cast<byte_t*>(p1); }

}

#endif
