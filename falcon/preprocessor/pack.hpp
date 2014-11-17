#ifndef FALCON_PREPROCESSOR_PACK_HPP
#define FALCON_PREPROCESSOR_PACK_HPP

#include <falcon/config.hpp>

#ifdef IN_IDE_PARSER
# define FALCON_PP_PACK(impl) impl
#else
# define FALCON_PP_PACK(...) __VA_ARGS__
#endif

#endif
