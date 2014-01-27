#ifndef FALCON_CPP_EXTEND_PACK_HPP
#define FALCON_CPP_EXTEND_PACK_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_EXTEND_PACK ...
#else
# define CPP_EXTEND_PACK
#endif

#endif
