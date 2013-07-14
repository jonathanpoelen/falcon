#ifndef _FALCON_CPP_EXTEND_PACK_HPP
#define _FALCON_CPP_EXTEND_PACK_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L && !defined(IN_IDE_PARSER)
# define CPP_EXTEND_PACK ...
#else
# define CPP_EXTEND_PACK
#endif

#endif
