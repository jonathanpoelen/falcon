#ifndef FALCON_CPP_PACK_HPP
#define FALCON_CPP_PACK_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L
# define CPP_PACK ...
# define CPP_OPTIONAL_PACK(name) , class... name
# define CPP_USE_OPTIONAL_PACK(name) , name...
#else
# define CPP_PACK
# define CPP_OPTIONAL_PACK(name)
# define CPP_USE_OPTIONAL_PACK(name)
#endif

#endif
