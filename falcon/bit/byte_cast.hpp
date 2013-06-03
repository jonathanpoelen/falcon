#ifndef FALCON_BIT_BYTE_CAST_HPP
#define FALCON_BIT_BYTE_CAST_HPP

#include <cstddef>

namespace falcon {

typedef unsigned char byte_t;

inline byte_t * byte_cast(void * p)
{ return reinterpret_cast<unsigned char*>(p); }

inline std::size_t byte_distance(void * p1, void * p2)
{ return reinterpret_cast<unsigned char*>(p2) - reinterpret_cast<unsigned char*>(p1); }

}

#endif
